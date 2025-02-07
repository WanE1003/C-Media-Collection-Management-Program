# C++ Media Collection Management Program
This project is a C++ program designed to manage various types of media data. The program reads data from CSV files and stores them in an appropriate data structure. It also provides sorting and data refinement features, utilizing STL containers for efficient data management and additional functionalities like calculating the average duration of episodes.

# Program Structure 
* **Data Files 📁**
  * The program reads data from the following CSV files: `book.csv`, `episodes.csv`, `movie.csv`, `tvshows.csv`.
* **Main Classes and Data Structures 🏛️**
  * **MediaItem:** A base class for all media items, containing common properties.
  * **Collection:** A class that stores and manages `MediaItem` objects in a `vector`.
  * **STL Container `(std::vector<MediaItem>)`:** Used for storing and manipulating data efficiently.
* **Features** ⚙️
  * Data Refinement (spellChecker function) 🛠️
  * Sorting Functionality
  * Average Episode Duration Calculation ⏱️
 
# **Technologies Used** 🖥️
* **C++ Standard Library (STL)**: Utilizes vector, algorithm, and other standard utilities
* **Looping & Iteration (algorithm, vector):** Used for iterating over media items efficiently
* **Accumulation (numeric):** Used for calculating total and average durations
* **String Processing (sstream):** Used for parsing CSV file contents
