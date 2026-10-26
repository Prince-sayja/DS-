# SmartMart: A Dynamic Grocery Inventory & Billing System

A console-based grocery store management application developed in **C** using **singly linked lists**. SmartMart replaces traditional static arrays with dynamic data structures to manage stock, handle customer carts, verify inventory in real-time, and calculate bills accurately.

---

## 📌 Project Overview
* **Domain:** Data Structures Mini Project (Semester 3 AI & DS)
* **Language:** C
* **Core Data Structure:** Singly Linked List
* **Memory Management:** Dynamic allocation using `malloc()` and `free()`

---

## 🚀 Key Features & Modules
1. **Inventory Management:** Dynamically insert and display grocery items without fixed-size limits.
2. **Product Search:** Fast product lookup using unique product IDs.
3. **Cart Management:** Add, update, and review items selected for purchase.
4. **Stock Control:** Real-time stock checks to prevent overselling, with automatic quantity deductions.
5. **Billing & Invoicing:** Calculates totals line by line and generates a clean receipt.
6. **Memory Cleanup:** Deallocates all dynamically allocated nodes on checkout and exit to prevent memory leaks.

---

## 🛠️ Data Structure Architecture

```
[Inventory Node] -> [ID | Name | Price | Quantity | Next*] ---> [Next Item] -> NULL
[Cart Node]      -> [ID | Name | Price | Quantity | Next*] ---> [Next Item] -> NULL
```

### Why Linked Lists?
* **Dynamic Sizing:** Items can be added or deleted at runtime without pre-allocating large arrays.
* **Non-Restricted Access:** Unlike Stacks (LIFO) or Queues (FIFO), shopping carts and inventory require random search, selective updates, and arbitrary deletion.

---

## 💻 How to Compile and Run

### 1. Compile with GCC
```bash
gcc main.c -o smartmart
```

### 2. Run the Program
* **On Linux / macOS:**
  ```bash
  ./smartmart
  ```
* **On Windows:**
  ```cmd
  smartmart.exe
  ```

---

## 👥 Team Members
* **Prince Sayja**
* **Shruti Panchal**
* **Shubham Rathod**

---

## 🔮 Future Scope
* Persistent file storage (save and load stock across sessions).
* Customer account management and purchase history.
* Graphical user interface (GUI) or web dashboard integration.
