# Task 9: Web Scraping

Your task is to create a scraper for products from e-commerce websites. Choose at least two e-shops from which you will gather product information.

- Input will be a search term such as `beats studio3`, based on which the e-shop will search for products.
- For each product, retrieve:
  - Name
  - Price
  - Description (must be from the product detail page)
  - Product link (detail)
- Attempt to remove irrelevant items from the list of products.
![Products](produkty.png)
- Display the acquired (relevant) items from all e-shops sorted by price in ascending order.

## Procedure

- Use the [Goutte](https://packagist.org/packages/fabpot/goutte) library or similar.
- Create an HTTP request to search for products based on the given search term.
- Iterate over each product and fetch its detail page.
- Extract and store the required data from the detail page.
- Remove irrelevant products from the stored data (e.g., based on product name or words in the description).
- Compile a clear listing of the acquired data sorted by price in ascending order.
