# C++ Polymorphic Image Processing Engine

This repository showcases a complete **C++ Object-Oriented Programming (OOP) project** designed as a library for manipulating images in the **Netpbm (P2/P3)** format.

The project demonstrates advanced C++ concepts such as**polymorphism**, **inheritance**, and **dynamic memory management**. The included **`main.cpp`** file provides a command-line interface (CLI) to demonstrate the library's functionality.

---

*  **CLI Commands & Operator Mapping**
  
  * **i <filename> as <$token>**	Import and load an image from a file.
  * **e <$token> as <filename>**	Export and save the image to a file.
  * **d <$token>**	Delete the image from the database/memory.
  * **n <$token>**	Apply Negative (Inversion).
  * **z <$token>**	Apply Rotation.
  * **m <$token>**	Apply Matching (Histogram Equalization).
  
  
* **Operator Overloading:** Image transformations are implemented as overloaded virtual operators, providing a clear and intuitive syntax:
    * **`operator+=`**: **Rotation** (Corrected to match the code)
    * **`operator*=`**: **Scaling/Resizing** (Corrected to match the code)
    * `operator!`: **Inversion** (Color/Brightness)
    * `operator~`: **Histogram Equalization** (Contrast Enhancement)

---

### Build and Run Instructions

1.  **Clone the Repository:**
    ```bash
    git clone [https://github.com/K0toulas/Cpp-Polymorphic-Image-Processor.git](https://github.com/K0toulas/Cpp-Polymorphic-Image-Processor.git)
    ```
2.  **Navigate and Compile:** (If you are not in the working directory)
    ```bash
    cd Cpp-Polymorphic-Image-Processor
    g++ *.cpp -o ImageProcessor
    ```
3.  **Run the Application:** Execute the compiled program to start the command-line interface.
    ```bash
    ./ImageProcessor
    ```

