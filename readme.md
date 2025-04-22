## How to Run
1. Open the project in CLion or your preferred C++ IDE.
2. Place the dataset CSV (`BooksDataset.csv`) in the working directory.
   - Can be found within the cmake-debug folder on Github
3. Build and run the project.
4. Use the menu to interact with the data.

## Features
- Load and parse CSV book data
- Clean author, genre, and price fields
- Search books by title, author, or genre
- Sort books by:
    - Title
    - Author
    - Price
    - Publication Date
- View Top-N most expensive books
- Benchmark QuickSort vs MergeSort (comparisons and time)
- Toggle ascending/descending order (default: descending)
- Recommend books based on a searched book's characteristics