#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Sizeinc constant defines how often memory is allocated
// during the processing of the string in case the user enters large number of characters
#define sizeinc 30

// 1 - output the list of all possible outcomes and their probabilities, 0 - do not output the list
#define list_probabilities 1
// Prec defines the length of a fraction of a probability
// Note that with high precision the numbers are not 100% correct
#define prec 6

// 1 - output a random outcome, 0 - do not output a random outcome
#define get_a_random_outcome 1

void input_string(char **ptstr)
{
	int cursize = sizeinc;
	int i = 0;
	while (1)
	{
		int c = getchar();
		if ((c == '\0') || (c == EOF) || (c == '\n')) 
		{
			(*ptstr)[i] = '\0';
			break;
		}
		else if (c != ' ')
		{
			(*ptstr)[i] = c;
			++i;
			if (i > cursize - 1) *ptstr = realloc(*ptstr, cursize += sizeinc);
		}
	}
	*ptstr = realloc(*ptstr, i + 1);
	return;
}

// There will be multiple operations with the string.
// The next function calculates such a length that it's not necessary to
// reallocate memory during the first transformation (numbers -> question marks). Optimization.
int max_len_qmarks(const char *str)

{
	int maxl = 1;
	int len = strlen(str);
	double prob;
	for (int i = 0; i <= len - 1; ++i)
		if (str[i] >= '0' && str[i] <= '9')
		{
			sscanf(str + i, "%lf", &prob);
			maxl += 3 + floor(prob); //it's not exactly the max len. Because the frac part may be 0
			while ((str[i] >= '0' && str[i] <= '9') || (str[i] == '.'))
				++i;
			--i;
		}
		else ++maxl;
	return maxl;
}

void def_strcpy(char *dest, const char *src)	// |dest| and |src| may overlap
{												// Buffer overflow protection (using strncpy)
	char *buf = malloc(strlen(src) + 3);
	strncpy(buf, src, strlen(src) + 1);
	strncpy(dest, buf, strlen(buf) + 1);
	free(buf);
	return;
}

void insert(char *dest, const char *ins, int pos) //pos: the beginning is pos == 0, after the 1st
// and before the 2nd elem is pos == 1, etc.
{
	char* bufr = malloc(strlen(dest) - pos + 1);
	strncpy(bufr, (const char *)(dest + pos), strlen(dest + pos) + 1);
	def_strcpy(dest + pos, ins);
	strncpy(dest + pos + strlen(ins), (const char *)bufr, strlen(bufr) + 1);
	free(bufr);
	return;
}

int get_number_of_options(const char *str)
{
	int res = 1;
	double prob;
	int parflag = 0;
	for (int i = 0; i <= strlen(str) - 1; ++i)
		if ((str[i] >= '0' && str[i] <= '9') && !parflag)
		{
			sscanf(str + i, "%lf", &prob);
			while ((str[i] >= '0' && str[i] <= '9') || str[i] == '.')
				++i;
			--i;
			if (floor(prob) - prob != 0)
				res <<= 1;
		}
		else if (str[i] == '\"') parflag ^= 1;
	return res;
}

void scale_array(double *arr, double prob, int options)
{
	double oppositeprob = 1 - prob;
	for (int i = options; i <= (options << 1) - 1; ++i)
		arr[i] = arr[i - options];
	for	(int i = 0; i <= options - 1; ++i)
		arr[i] = arr[i] * prob;
	for (int i = options; i <= (options << 1) - 1; ++i)
		arr[i] = arr[i] * oppositeprob;
	return;
}

double *get_options(const char *str) //get an array of options with the probabilities
{
	double *res = malloc(sizeof(double) * get_number_of_options(str));
	res[0] = 1;
	int opts = 1;
	double prob;
	int parflag = 0;
	for (int i = 0; i <= strlen(str) - 1; ++i)
		if ((str[i] >= '0' && str[i] <= '9') && !parflag)
		{
			sscanf(str + i, "%lf", &prob);
			while ((str[i] >= '0' && str[i] <= '9') || str[i] == '.')
				++i;
			--i;
			if (floor(prob) - prob != 0)
			{
				scale_array(res, prob - floor(prob), opts);
				opts <<= 1;
			}
		}
		else if (str[i] == '\"') parflag ^= 1;
	return res;
}

double generate_prob(void) //randomly generates a number of "double" type BETWEEN 0 AND 1
// extending <precision> digits after the comma (15 is double precision)
{
	double res;
	int precision = 15; // <- Limitation on the number of options (double precision)
	char *tmpstr = malloc(3 + precision);
	tmpstr[0] = '0';
	tmpstr[1] = '.';
	for (int i = 0; i <= precision - 1; ++i)
		tmpstr[i + 2] = '0' + rand() % 10;
	sscanf(tmpstr, "%lf", &res);
	free(tmpstr);
	return res;
}

int generate_option(const double *probabilities) // chooses one of the "numbers -> question marks"
// transformation options according to the probabilities. 
// (Randomly generates a transformation key)
{
	double dkey = generate_prob();
	int key; // <- Limitation on the number of options (size of int in bits)
	double tmpd = probabilities[0];
	for (key = 1; dkey >= tmpd; ++key)
		tmpd += probabilities[key]; // <- Limitation on the number of options (max. possible dynamic array size)
	return key - 1;
}

void numbers_to_qmarks(char **str, int key) // The key defines the exact transformation.
// Key description: key is a binary number. Each binary digit defines the option of transformation on every stage.
// Example: Suppose we have 5 real numbers with non-zero fraction in the string,
// then a key is a binary number of the next form: xxxxx - from 00000 to 11111.
// A one stands for N-1 (less) quest. marks and a zero is for N (more) (N is not a const).
// One of the keys: 01001. Here, the following branches are picked:
// The 1st transformation: less q. marks; 2nd - more; 3rd - more; 4th - less; 5th - more.
{
	int cntr = 0, cursize = strlen(*str) + 1, parflag = 0;
	for (int i = 0; i <= strlen(*str); ++i)
		if (((*str)[i] >= '0' && (*str)[i] <= '9') && !parflag)
		{
			double num;
			sscanf(*str + i, "%lf", &num);	
			int qm;
			if (num - floor(num) != 0)
			{
				if ((key >> cntr) & 1) 
					qm = num;
				else qm = num + 1;
				++cntr;
			}
			else qm = num;
			char *tmps = malloc(qm + 3);
			memset(tmps + 1, '?', qm);
			tmps[0]='\"';
			tmps[qm + 1] = '\"';
			tmps[qm + 2] = '\0';
			int oldpos = i;
			while (((*str)[i] <= '9' && (*str)[i] >= '0') || (*str)[i] == '.')
				++i;
			def_strcpy(*str + oldpos, *str + i);
			while (cursize < strlen(*str) + strlen(tmps) + 1)
				cursize += sizeinc;
			*str = realloc(*str, cursize);
			insert(*str, (const char *)tmps, oldpos);
			free(tmps);
			i = oldpos + qm + 1;
		}
		else if ((*str)[i] == '\"') parflag ^= 1;
	return;
}

void subtract_aux1(char *str1, const char* str2) // 1st arg is the result (str1)
{
	if (strlen(str2) == 0) return;
	for (int i = 0; i <= strlen(str2); ++i)
	{
		if (strlen(str1) == 0) return;
		if (str2[i] != '?')
		{
			for (int j = 0; j <= strlen(str1) - 1; ++j)
				if (str1[j] == '?')
				{
					def_strcpy(str1 + j, str1 + j + 1);
					break;
				}
				else if (str1[j] == str2[i])
				{
					def_strcpy(str1 + j, str1 + j + 1);
					break;
				}
		}
		else def_strcpy(str1, str1 + 1);
	}
	return;
}

void subtract_aux(char *str, int *i)
{
	int pos1 = *i - 1;
	while (str[pos1] != '\"') --pos1;
	int pos2 = *i + 3;
	while (str[pos2] != '\"') ++pos2;
	char *buf1 = malloc(*i + 3 - (pos1 + 1));
	char *buf2 = malloc(pos2 - (*i + 3) + 1);
	buf1[*i - (pos1 + 1)] = '\0';
	buf2[pos2 - (*i + 3)] = '\0';
	memcpy(buf1, str + pos1 + 1, *i - (pos1 + 1));
	memcpy(buf2, str + *i + 3, pos2 - (*i + 3));
	subtract_aux1(buf1, buf2);
	def_strcpy(str + pos1, str + pos2 + 1);
	def_strcpy(buf1 + 1, buf1);
	buf1[0] = '\"';
	buf1[strlen(buf1) + 1] = '\0';
	buf1[strlen(buf1)] = '\"';
	insert(str, buf1, pos1);
	*i = pos1 + strlen(buf1) - 2;
	free(buf1);
	free(buf2);
	return;
}

void concat_and_subtract(char *str)
{
	int parflag = 0;
	for (size_t i = 0; i <= strlen(str) - 3; ++i)
	{
		if (strlen(str) < 4) return;
		if (str[i] == '\"')
		{
			parflag ^= 1;
			if ((str[i + 1] == '-' && str[i + 2] == '\"') && !parflag)
			{
				subtract_aux(str, (int *)&i);
				parflag ^= 1;
			}
			else if ((str[i + 1] == '+' && str[i + 2] == '\"') && !parflag)
			{
				def_strcpy(str + i, str + i + 3);
				parflag ^= 1;
				--i;
			}
		}
	}
	return;
}

void multiply_aux2(char *str1, const char *str2)
{
	for (size_t i = 0; i < strlen(str1); ++i)
		if (str1[i] == '?')
		{
			def_strcpy(str1 + i, str1 + i + 1);
			insert(str1, str2, i);
			i += strlen(str2) - 1;
		}
	return;
}

void multiply_aux1(char **str1, char *str2)
{	
	char *res;
	int qmarks1 = 0, qmarks2 = 0;
	for (int i = 0; i <= strlen(*str1); ++i)
		if ((*str1)[i] == '?') ++qmarks1;
	for (int i = 0; i <= strlen(str2); ++i)
		if (str2[i] == '?') ++qmarks2;
	int max = strlen((*str1)) - qmarks1 + qmarks1 * strlen(str2);
	if (strlen(str2) - qmarks2 + qmarks2 * strlen(*str1) > max)
	{
		max = strlen(str2) - qmarks2 + qmarks2 * strlen(*str1) + 1;
		if (strlen(str2) + 3 > max + 2)
			res = malloc(strlen(str2) + 3);
		else res = malloc(max + 2);
		strncpy(res + 1, str2, strlen(str2) + 1);
		multiply_aux2(res + 1, *str1);
	}
	else
	{
		++max;
		if (strlen(*str1) + 3 > max + 2)
			res = malloc(strlen(*str1) + 3);
		else res = malloc(max + 2);
		strncpy(res + 1, *str1, strlen(*str1) + 1);
		multiply_aux2(res + 1, str2);
	}
	res[0] = '\"';
	res[strlen(res) + 1] = '\0';
	res[strlen(res)] = '\"';
	*str1 = realloc(*str1, max + 2);
	strncpy(*str1, res, strlen(res) + 1);
	free(res);
	return;
}

void multiply_all(char **str)
{
	int cursize = strlen(*str) + 1;
	int parflag = 0;
	for (size_t i = 0; i <= strlen(*str); ++i)
	{
		if (strlen(*str) < 4) return;
		if ((*str)[i] == '\"')
		{
			parflag ^= 1;
			if (((*str)[i + 1] == '*' && (*str)[i + 2] == '\"') && !parflag)
			{
				int pos1 = i - 1;
				while ((*str)[pos1] != '\"') --pos1;
				int pos2 = i + 3;
				while ((*str)[pos2] != '\"') ++pos2;
				char *buf1 = malloc(i + 1 - (pos1 + 1));
				char *buf2 = malloc(pos2 - (i + 3) + 1);
				buf1[i - (pos1 + 1)] = '\0';
				buf2[pos2 - (i + 3)] = '\0';
				memcpy(buf1, *str + pos1 + 1, i - (pos1 + 1));
				memcpy(buf2, *str + i + 3, pos2 - (i + 3));
				multiply_aux1(&buf1, buf2);
				def_strcpy(*str + pos1, *str + pos2 + 1);
				if (cursize < strlen(*str) + strlen(buf1) + 1)
				{
					cursize += sizeinc;
					while (cursize < strlen(*str) + strlen(buf1) + 1)
						cursize += sizeinc;
					*str = realloc(*str, cursize);
				}
				insert(*str, buf1, pos1);
				i = pos1 + strlen(buf1) - 2;
				free(buf1);
				free(buf2);
				parflag ^= 1;
			}
		}
	}
	return;
}

void process_str(char **str)
{
	int parpos1, parpos2 = 0, cursize = strlen(*str) + 1;

	while (1)
	{
		for (; (*str)[parpos2] != ')' && parpos2 < strlen(*str); ++parpos2);
		if ((*str)[parpos2] == '\0') break;
		for (parpos1 = parpos2 - 1; (*str)[parpos1] != '('; --parpos1); //Not enough parentheses event not processed
		char *buf = malloc(parpos2 - parpos1);
		strncpy(buf, *str + parpos1 + 1, parpos2 - (parpos1 + 1));
		buf[parpos2 - parpos1 - 1] = '\0';
		multiply_all(&buf);
		concat_and_subtract(buf);
		def_strcpy(*str + parpos1, *str + parpos2 + 1);
		cursize -= parpos2 + 1 - parpos1;
		while (cursize < strlen(*str) + strlen(buf) + 1)
			cursize += sizeinc;
		*str = realloc(*str, cursize);
		insert(*str, buf, parpos1);
		parpos2 = parpos1 + strlen(buf) - 1;
		free(buf);
	}
	multiply_all(str);
	concat_and_subtract(*str);
	*str = realloc(*str, strlen(*str) + 1); //Getting rid of unnecessary characters
	return;
}

void transform_qmarks(char *str)
{
	if (strlen(str) < 2) return;
	int i = 0;
	if (str[0] == '\"')
		while (str[i + 1] == '?')
			++i;
	if (str[i + 1] == '\"')
		if (str[i + 2] == '\0')
			sprintf(str, "%d", i);
	return;
}

typedef struct StrProb 
{
	char *str;
	double prob;
} Tprob;

int cmpr (Tprob **s1, Tprob **s2)
{
	return ((*s2)->prob > (*s1)->prob?1:((*s1)->prob == (*s2)->prob?0:-1));
}

void qsort_f(char **strarr, double *probs, int arrsize)
{
	Tprob **parr = malloc(arrsize * sizeof(Tprob *));
	for (int i = 0; i <= arrsize - 1; ++i)
	{
		parr[i] = malloc(sizeof(Tprob));
		parr[i]->str = strarr[i];
		parr[i]->prob = probs[i];
	}
	
	qsort(parr, arrsize, sizeof(Tprob *), (int (*)(const void *, const void *))cmpr);

	for (int i = 0; i <= arrsize - 1; ++i)
	{
		probs[i] = parr[i]->prob;
		strarr[i] = parr[i]->str;
		free(parr[i]);
	}
	free(parr);
	return;
}

// Note: At least 15 real numbers with non-zero fraction in the string are supported.
// According to the conditions, the correctness IS NOT checked.
// Considering there are only 3 operations (+, -, *) with 2 levels of priority,
// it was decided not to use postfix form (=> stack) as a stage of processing.
int main(int argc, char *argv[])
{
	srand(time(NULL));
	char *s = malloc(sizeinc);
	input_string(&s);	// analogical to scanf("%s", ...) but ignoring all spaces and doesn't return anything
	if (strlen(s) == 0) 
	{
		free(s);
		return 0;
	}
	s = realloc(s, max_len_qmarks(s)); // optimization
	double *probs = get_options(s);
	printf("\n////////////////////////////////////////\n");

#if get_a_random_outcome
{
	printf("----------------------------------------\n");
	int opt = generate_option(probs);
	char *sc = malloc(max_len_qmarks(s));
	strncpy(sc, s, strlen(s) + 1);
	numbers_to_qmarks(&sc, opt);
	process_str(&sc);
	transform_qmarks(sc);
	printf(" Random outcome:\n %s\n", sc);
	free(sc);
}
#endif

#if list_probabilities
{
	printf("----------------------------------------\n");
	printf("    Probability    |    Outcome\n");
	int n = get_number_of_options(s);
	int maxl = max_len_qmarks(s);
	char **strarr = malloc(sizeof(char*) * n);
	double *arrcp = malloc(sizeof(double) * n);;
	for (int i = 0; i <= n - 1; ++i)
	{
		arrcp[i] = probs[i];
		strarr[i] = malloc(maxl);
		strncpy(strarr[i], s, strlen(s) + 1);
		numbers_to_qmarks(strarr + i, i);
		process_str(&strarr[i]);
		transform_qmarks(strarr[i]);
	}

	for (int i = 0; i <= n - 2; ++i)
		for(int j = i + 1; j <= n - 1; ++j)
			if (strcmp(strarr[i], strarr[j]) == 0)
			{
				arrcp[i] += arrcp[j];
				if (j != n - 1)
				{
					arrcp[j] = arrcp[n - 1];
					free(strarr[j]);
					strarr[j] = strarr[n - 1];
					--j;
				}
				else
					free(strarr[n - 1]);
				--n;
			}

	qsort_f(strarr, arrcp, n);
	int preccheck;
	if (prec <= 0) preccheck = 1;
	else preccheck = prec;
	double precs = 1;
	for (int i = 0; i <= preccheck - 1; ++i)
		precs *= 0.1;
	for (int i = 0; i <= n - 1; ++i)
		if (arrcp[i] < precs)
		{
			char *staux = malloc(100);
			sprintf(staux, "<%.*lf", preccheck, precs);
			printf("%16s   | %s\n", staux, strarr[i]);		
			free(staux);
		}
		else
			printf("%16.*lf   | %s\n", preccheck, arrcp[i], strarr[i]);
	for (int i = 0; i <= n - 1; ++i)
		free(strarr[i]);
	free(arrcp);
	free(strarr);
}	
#endif
	
	free(probs);
	free(s);
	printf("----------------------------------------\n");
	printf("////////////////////////////////////////\n\n");
	return 0;
}
