// Description of the task is here --> https://github.com/oscar-foxtrot/University_stuff/tree/main/Cpp_practice_Shelf

#include <iostream>
#include <climits>

#define DISPLAY_MAG true // Change to "false" if you don't want to see the titles of mags(journals) on the output
#define NUMBER_ARTICLE_TITLES true // Change to "false" if you don't want the articles to be numbered on the output
#define MAX_MAG_LENGTH INT_MAX // Mag (journal) titles longer than this value are truncated and followed by "..." on the output (if DISPLAY_MAG is true)
#define MAX_ARTICLE_TITLE_LENGTH INT_MAX // Article titles longer than this value are truncated and followed by "..." on the output

class Book;
class Mag;

class Shelf // Ideally the literature is sorted and advantage of this fact is taken though. This implementation does not encompass that.
{
public:
    Shelf(): nbooks(0), nmags(0) {}
    ~Shelf();
    int add(const Book &book); // Returns 0 if successful, 1 - if the shelf can't hold any more papers
    int add(const Mag &mag); // Returns 0 if successful, 1 - if the shelf can't hold any more papers

    // Print all article titles meeting the conditions specified. If you want to search by any first/last symbol
    // in the article's title, specify as the "first_symbol" or the "last_symbol" parameter '\0'.
    // If you just want to print all article titles, don't pass parameters
    // If you want to display the title of the mag where the article was found, specify 'true' as display_mag, otherwise specify false.
    void print_article_titles(int minimal_number_of_pages=0, const std::string &first_symbols="\0", char last_symbol='\0') const;

    // Print the titles of magazines with articles with the same names
    // Data unsorted. Complexity is O(n^2) if comparing two mags considered O(1)
    void print_same() const;

    void clear_shelf();
    int get_capacity() const;

private:
    static const int capacity = 100; // Non-static capacity would complicate things too much
    int nbooks;
    int nmags;
    Mag *mags[capacity];
    Book *books[capacity];
};

class Paper // Common base class for classes: Book, Mag
{
public:
    Paper(const std::string &title): title(title) {}
    std::string get_title() const;

private:
    std::string title;
};

class Book: public Paper
{
public:
    Book(const std::string &title, int number_of_pages): Paper(title), npages(number_of_pages) {}
    int get_npages() const;

private:
    int npages;
};

class Mag: public Paper
{
public:
    Mag(const std::string &title): Paper(title), narts(0) {}

    // Returns 0 if successful, 1 in case the magazine can't hold any more articles
    int add_article(const std::string &title, int number_of_pages);

    // Get a list containing the titles of the articles. bufsize is how many strings the buffer can hold. 0 - success, 1 - fail
    int get_article_titles(std::string *buf, int bufsize) const;

    // Get a list containing numbers of pages in corresponding articles. bufsize is how many ints the buffer can hold. 0 - success, 1 - fail
    int get_art_pages(int *buf, int bufsize) const;
    
    int get_number_of_articles() const;
    static int get_capacity(); // Returns the number of articles the mag can hold 
    void clear_mag();

private:
    static const int capacity = 100; // Non-static capacity would complicate things too much
    int narts;
    std::string arts[capacity]; // Using an array as the internal representation
    int artpages[capacity]; // This way, "find" command can be used
};


int main(int argc, char *argv[])
{
    // Let's compare the staff's scientific work.
    // This way, articles with the same name meaning co-authorship
    Mag mags[] = {Mag("Borisov A.V."), Mag("Gorshenin A.K."), Mag("Bening V.E."), Mag("Doynikov A.N.")};

    mags[0].add_article("2022 Identification of Continuous-Discrete Hidden Markov Models with Multiplicative Observation Noise", 17);
    mags[0].add_article("2021 Minimax Estimation in Regression under Sample Conformity Constraints", 10);
    mags[0].add_article("2020 L1-Optimal Filtering of Markov Jump Processes. II. Numerical Analysis of Particular Realizations Schemes", 21);

    mags[1].add_article("2022 Identification of Continuous-Discrete Hidden Markov Models with Multiplicative Observation Noise", 17);
    mags[1].add_article("2022 Preface to the Special Issue on \"Control, Optimization, and Mathematical Modeling of Complex Systems\"", 13);
    mags[1].add_article("2021 On the efficiency of machine learning algorithms for imputation in spatiotemporal meteorological data", 10);
    mags[1].add_article("2014 Variance-mean mixtures as asymptotic approximations", 7);

    mags[2].add_article("2023 Comparing Compound Poisson Distributions by Deficiency: Continuous-Time Case", 12);
    mags[2].add_article("2022 Comparing Distributions of Sums of Random Variables by Deficiency: Discrete Case", 15);
    mags[2].add_article("2018 On the asymptotic behavior of the deficiency of some statistical estimators based on samples with random sizes", 10);
    mags[2].add_article("2014 Variance-mean mixtures as asymptotic approximations", 7);

    mags[3].add_article("2021 A bound for the distribution Smirnov's statistics", 21);
    mags[3].add_article("1991 Optimization of multiple channel queue with simultaneous service by non-identical servers", 6);
    mags[3].add_article("2015 Estimating Risk of Dynamic Trading Strategies from High Frequency Data Flow", 13);

    Book some_books[] = {Book("War and peace", 1225), Book("The Great Gatsby", 137), Book("The C++ Programming Language", 1366)};
    Shelf shelf0; // default ctor called
    shelf0.add(some_books[0]);
    shelf0.add(mags[0]);
    shelf0.add(mags[3]);
    shelf0.add(some_books[2]);
    shelf0.add(mags[1]);
    shelf0.add(some_books[1]);
    shelf0.add(mags[2]);
    
    // Shelf initialized. Testing:
    // void print_article_titles(int minimal_number_of_pages=0, const std::string &first_symbols="\0", char last_symbol='\0') const;

    std::cout << "\nTEST1: All articles\n" << std::endl;
    shelf0.print_article_titles(); // Print all article titles ✓

    std::cout << "\nTEST2: Not shorter than 20 pages\n";
    shelf0.print_article_titles(20); // Articles not shorter than 20 pages ✓

    std::cout << "\nTEST3: Starting with \"Comparing\"\n";
    shelf0.print_article_titles(0, "Comparing"); // Article titles starting with "Comparing" ✓

    std::cout << "\nTEST4: Starting with \"2022\"\n";
    shelf0.print_article_titles(0, "2022"); // Article titles starting with "Comparing" ✓

    std::cout << "\nTEST5: Starting with \"2022\", ending with 'e'\n";
    shelf0.print_article_titles(0, "2022", 'e'); // Article titles starting with "2022", ending with 'e' ✓

    std::cout << "\nTEST6: Co-authorship\n";
    shelf0.print_same(); // Mags (journals) containing articles with the same titles ✓

    std::cout << std::endl;
    return 0;
}


Shelf::~Shelf()
{
    for (--nbooks; nbooks >= 0; --nbooks)
    {
        delete books[nbooks];
    }
    for (--nmags; nmags >= 0; --nmags)
    {
        delete mags[nmags];
    }
}

int Shelf::add(const Book &book)
{
    if (nbooks + nmags == capacity)
    {
        return 1;
    }
    books[nbooks] = new Book(book); // Copy ctor for Book is called
    ++nbooks;
    return 0;
}

int Shelf::add(const Mag &mag)
{
    if (nbooks + nmags == capacity)
    {
        return 1;
    }
    mags[nmags] = new Mag(mag); // Copy ctor for Mag is called
    ++nmags;
    return 0;
}

void Shelf::print_article_titles(int minimal_number_of_pages, const std::string &first_symbols, char last_symbol) const
{
    int bufsz = Mag::get_capacity();
    std::string *art_titles = new std::string[bufsz];
    int *art_pages = new int[bufsz];
    bool unconditional_search = minimal_number_of_pages == 0 && first_symbols == "\0" && last_symbol == '\0';
    bool found = false;

    for (int i = 0; i < nmags; ++i)
    {
        int n = mags[i]->get_number_of_articles();
        mags[i]->get_article_titles(art_titles, bufsz);
        mags[i]->get_art_pages(art_pages, bufsz);
        int counter = 1;
        for (int j = 0; j < n; ++j)
        {
            bool condition;
            condition = unconditional_search
                || (art_pages[j] >= minimal_number_of_pages)
                && (first_symbols == "\0" || art_titles[j].find(first_symbols) == 0) // Find method used as hinted in the task
                && (last_symbol == '\0' || art_titles[j][art_titles[j].length() - 1] == last_symbol);
            if (condition)
            {
                found = true;
                int max_title_length = MAX_ARTICLE_TITLE_LENGTH;
                if (NUMBER_ARTICLE_TITLES)
                {
                    std::cout << i + 1 << '.' << counter << ") ";
                }
                if (art_titles[j].length() > max_title_length)
                {
                    std::cout << art_titles[j].substr(0, max_title_length) << "...";
                }
                else
                {
                    std::cout << art_titles[j];
                }
                if (DISPLAY_MAG)
                {
                    const std::string &title = mags[i]->get_title();
                    max_title_length = MAX_MAG_LENGTH;
                    if (title.length() > max_title_length)
                    {
                        std::cout << " (" << title.substr(0, max_title_length) << "...)";
                    }
                    else
                    {
                        std::cout << " (" << title << ")";
                    }
                }
                ++counter;
                std::cout << std::endl;
            }
        }
    }
    if (!found)
    {
        std::cout << "Articles not found" << std::endl;
    }
    
    delete[] art_titles;
    delete[] art_pages;
}

void Shelf::print_same() const
{
    int bufsz = Mag::get_capacity();
    std::string *prim_art_titles = new std::string[bufsz];
    std::string *sec_art_titles = new std::string[bufsz];
    bool global_found = false;

    for (int i = 0; i < nmags; ++i)
    {
        mags[i]->get_article_titles(prim_art_titles, bufsz);
        int nprim = mags[i]->get_number_of_articles();
        for (int k = i + 1; k < nmags; ++k)
        {
            mags[k]->get_article_titles(sec_art_titles, bufsz);
            int nsec = mags[k]->get_number_of_articles();

            bool found = false;
            for (int i1 = 0; i1 < nprim; ++i1)
            {
                for (int j1 = 0; j1 < nsec; ++j1)
                {
                    if (prim_art_titles[i1] == sec_art_titles[j1])
                    {
                        std::string title1 = mags[i]->get_title();
                        std::string title2 = mags[k]->get_title();
                        if (title1.length() > MAX_MAG_LENGTH)
                        {
                            title1 = title1.substr(0, MAX_MAG_LENGTH);
                        }
                        if (title2.length() > MAX_MAG_LENGTH)
                        {
                            title2 = title2.substr(0, MAX_MAG_LENGTH);
                        }
                        found = true;
                        global_found = true;
                        std::cout << '\"' << title1 << "\" and \"" << title2 << '\"' << std::endl;
                        break;
                    }
                }
                if (found)
                {
                    break;
                }
            }
        }
    }

    if (!global_found)
    {
        std::cout << "All mags/journals are unique" << std::endl;
    }
    delete[] prim_art_titles;
    delete[] sec_art_titles;
}

void Shelf::clear_shelf()
{
    this->~Shelf();
}

int Shelf::get_capacity() const
{
    return capacity;
}

std::string Paper::get_title() const
{
    return title;
}

int Book::get_npages() const
{
    return npages;
}

int Mag::add_article(const std::string &title, int number_of_pages)
{
    if (narts == capacity)
    {
        return 1;
    }
    arts[narts] = title;
    artpages[narts] = number_of_pages;
    ++narts;
    return 0;
}

int Mag::get_article_titles(std::string *buf, int bufsize) const
{
    if (bufsize < narts)
    {
        return 1;
    }
    for (int i = 0; i < narts; ++i)
    {
        buf[i] = arts[i];
    }
    return 0;
}

int Mag::get_art_pages(int *buf, int bufsize) const
{
    if (bufsize < narts)
    {
        return 1;
    }
    for (int i = 0; i < narts; ++i)
    {
        buf[i] = artpages[i];
    }
    return 0;
}

int Mag::get_capacity()
{
    return capacity;
}

int Mag::get_number_of_articles() const
{
    return narts;
}

void Mag::clear_mag()
{
    for (--narts; narts >= 0; --narts)
    {
        arts[narts].clear();
    }
}
