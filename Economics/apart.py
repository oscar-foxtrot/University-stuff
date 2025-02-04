import matplotlib.pyplot as plt
import numpy as np

def calculate_wealth(investment_rate, mortgage_rate, rent_rate, salary_rate, apartment_price, n):

    salary = salary_rate * (1 / 12) * apartment_price  # Salary per month
    rent = rent_rate * (1 / 12) * apartment_price  # Rent per month
    disposable_income = salary - rent  # Disposable income per month
    monthly_investment_rate = (1 + investment_rate) ** (1 / 12) - 1
    monthly_mortgage_rate = mortgage_rate * (1 / 12)

    result_mortgage = 0
    result_rent = 0
    loan_body_left = apartment_price

    if salary < rent:
        if salary < apartment_price * monthly_mortgage_rate:
            return (0, 0)
        else:
            for i in range(n):
                # Case "mortgage"
                loan_body_left *= monthly_mortgage_rate
                loan_body_left -= salary
                # If loan is paid then starting to invest with the money from rent
                if loan_body_left < 0:
                    result_mortgage += -loan_body_left
                    loan_body_left = 0
                elif loan_body_left == 0:
                    result_mortgage *= 1 + monthly_investment_rate
                    result_mortgage += rent + salary
                result_mortgage += apartment_price - loan_body_left
            return (0, result_mortgage)

    if salary < apartment_price * monthly_mortgage_rate:
        if salary < rent:
            return (0, 0)
        else:
            for i in range(n):
                # Case "rent"
                result_rent *= 1 + monthly_investment_rate
                result_rent += disposable_income
            return (result_rent, 0)

    res_rent_list = [0]
    res_mortgage_list = [0]
    total_payment = 0

    for i in range(n):
        # Case "rent"
        result_rent *= 1 + monthly_investment_rate
        result_rent += disposable_income

        # Case "mortgage"
        if loan_body_left > 0:
            total_payment += loan_body_left * monthly_mortgage_rate + salary
            loan_body_left += loan_body_left * monthly_mortgage_rate
            loan_body_left -= salary
        # If loan is paid then starting to invest with the money from rent
        elif loan_body_left < 0:
            print(i, total_payment)
            result_mortgage += -loan_body_left + salary
            loan_body_left = 0
        else:
            result_mortgage *= 1 + monthly_investment_rate
            result_mortgage += salary
        res_rent_list += [result_rent]
        res_mortgage_list += [result_mortgage + (apartment_price - loan_body_left)]


    return (res_rent_list, res_mortgage_list)


# The rates are given as per year

salary = 100000  # Salary
investment_rate = 0.1  # Investments interest rate
mortgage_rate = 0.06  # Mortgage interest rate
rent_rate = 0.05  # Rent rate (rent expressed as the percent of the apartment price)
apartment_price = 10000000  # Apartment price
n = 400 # Number of months passing before the final wealth comparison

salary_rate = salary / apartment_price * 12   # Salary rate (salary expressed as the percent of the apartment price)


res = calculate_wealth(investment_rate, mortgage_rate, rent_rate, salary_rate, apartment_price, n)
plt.plot(np.linspace(0, n, n + 1), res[0], label="rent")
plt.plot(np.linspace(0, n, n + 1), res[1], label="mortgage")
plt.legend()
plt.show()