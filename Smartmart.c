#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a singly linked list node
typedef struct Node {
    int id;
    char name[50];
    float price;
    int quantity;
    struct Node *next;
} Node;

// Global pointers for Inventory and Cart linked lists
Node *inventoryHead = NULL;
Node *cartHead = NULL;

// Function to create a new node
Node* createNode(int id, const char *name, float price, int quantity) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->price = price;
    newNode->quantity = quantity;
    newNode->next = NULL;
    return newNode;
}

// Module 1: Add product to inventory
void addInventoryProduct(int id, const char *name, float price, int quantity) {
    Node *newNode = createNode(id, name, price, quantity);
    if (inventoryHead == NULL) {
        inventoryHead = newNode;
    } else {
        Node *temp = inventoryHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Module 1: Display current inventory
void displayInventory() {
    if (inventoryHead == NULL) {
        printf("\nInventory is empty!\n");
        return;
    }
    printf("\n================ AVAILABLE INVENTORY ================\n");
    printf("%-8s %-20s %-12s %-10s\n", "ID", "Name", "Price ($)", "Stock");
    printf("-----------------------------------------------------\n");
    Node *temp = inventoryHead;
    while (temp != NULL) {
        printf("%-8d %-20s %-12.2f %-10d\n", temp->id, temp->name, temp->price, temp->quantity);
        temp = temp->next;
    }
    printf("=====================================================\n");
}

// Module 2: Search product by ID in inventory
Node* searchProduct(int id) {
    Node *temp = inventoryHead;
    while (temp != NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Module 3 & 4: Add to Cart & Stock Management
void addToCart() {
    int id, qty;
    displayInventory();

    printf("\nEnter Product ID to buy: ");
    if (scanf("%d", &id) != 1) return;

    Node *item = searchProduct(id);
    if (item == NULL) {
        printf("Error: Product ID not found in inventory!\n");
        return;
    }

    printf("Enter Quantity: ");
    if (scanf("%d", &qty) != 1 || qty <= 0) {
        printf("Error: Invalid quantity entered.\n");
        return;
    }

    // Check available stock
    if (item->quantity < qty) {
        printf("Error: Insufficient stock! Available: %d\n", item->quantity);
        return;
    }

    // Deduct stock from inventory
    item->quantity -= qty;

    // Check if product is already in the cart
    Node *cartTemp = cartHead;
    while (cartTemp != NULL) {
        if (cartTemp->id == id) {
            cartTemp->quantity += qty;
            printf("Updated cart: %d unit(s) of %s added.\n", qty, item->name);
            return;
        }
        cartTemp = cartTemp->next;
    }

    // Otherwise, create a new cart node
    Node *cartItem = createNode(item->id, item->name, item->price, qty);
    if (cartHead == NULL) {
        cartHead = cartItem;
    } else {
        cartTemp = cartHead;
        while (cartTemp->next != NULL) {
            cartTemp = cartTemp->next;
        }
        cartTemp->next = cartItem;
    }

    printf("Added %d unit(s) of %s to your cart!\n", qty, item->name);
}

// Module 3: View Cart items
void viewCart() {
    if (cartHead == NULL) {
        printf("\nYour cart is currently empty!\n");
        return;
    }
    printf("\n=================== YOUR CART ===================\n");
    printf("%-8s %-20s %-12s %-10s\n", "ID", "Name", "Price ($)", "Qty");
    printf("-------------------------------------------------\n");
    Node *temp = cartHead;
    while (temp != NULL) {
        printf("%-8d %-20s %-12.2f %-10d\n", temp->id, temp->name, temp->price, temp->quantity);
        temp = temp->next;
    }
    printf("=================================================\n");
}

// Free a linked list from memory
void freeList(Node **head) {
    Node *current = *head;
    Node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

// Module 5: Billing & Checkout
void checkout() {
    if (cartHead == NULL) {
        printf("\nCart is empty. Nothing to bill!\n");
        return;
    }

    float subtotal = 0.0f;
    printf("\n=====================================================\n");
    printf("                  SMARTMART INVOICE                  \n");
    printf("=====================================================\n");
    printf("%-8s %-18s %-8s %-10s %-10s\n", "ID", "Item", "Qty", "Price", "Total");
    printf("-----------------------------------------------------\n");

    Node *temp = cartHead;
    while (temp != NULL) {
        float itemTotal = temp->price * temp->quantity;
        subtotal += itemTotal;
        printf("%-8d %-18s %-8d $%-9.2f $%-9.2f\n", 
               temp->id, temp->name, temp->quantity, temp->price, itemTotal);
        temp = temp->next;
    }

    printf("-----------------------------------------------------\n");
    printf("FINAL BILL AMOUNT:                     $%.2f\n", subtotal);
    printf("=====================================================\n");
    printf("Thank you for shopping at SmartMart!\n");

    // Clear cart memory after checkout
    freeList(&cartHead);
}

// Initialize starter inventory items
void initializeInventory() {
    addInventoryProduct(101, "Milk (1L)", 2.50, 20);
    addInventoryProduct(102, "Bread (Whole Wheat)", 1.80, 15);
    addInventoryProduct(103, "Eggs (Dozen)", 3.20, 30);
    addInventoryProduct(104, "Rice (1kg)", 4.00, 25);
    addInventoryProduct(105, "Apples (1kg)", 3.00, 10);
}

int main() {
    int choice;
    initializeInventory();

    while (1) {
        printf("\n========= SMARTMART MANAGEMENT SYSTEM =========\n");
        printf("1. View Inventory\n");
        printf("2. Buy Product (Add to Cart)\n");
        printf("3. View Cart\n");
        printf("4. Add New Product to Inventory (Admin)\n");
        printf("5. Checkout & Generate Bill\n");
        printf("6. Exit\n");
        printf("Enter your choice (1-6): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Exiting...\n");
            break;
        }

        switch (choice) {
            case 1:
                displayInventory();
                break;
            case 2:
                addToCart();
                break;
            case 3:
                viewCart();
                break;
            case 4: {
                int id, qty;
                char name[50];
                float price;

                printf("Enter Product ID: ");
                scanf("%d", &id);

                if (searchProduct(id) != NULL) {
                    printf("Error: Product with ID %d already exists!\n", id);
                    break;
                }

                printf("Enter Product Name: ");
                scanf(" %[^\n]", name);
                printf("Enter Unit Price ($): ");
                scanf("%f", &price);
                printf("Enter Initial Stock Quantity: ");
                scanf("%d", &qty);

                addInventoryProduct(id, name, price, qty);
                printf("Product '%s' successfully added to inventory.\n", name);
                break;
            }
            case 5:
                checkout();
                break;
            case 6:
                // Module 6: Free all remaining dynamically allocated memory
                freeList(&inventoryHead);
                freeList(&cartHead);
                printf("\nMemory cleaned up successfully. Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice! Please select an option between 1 and 6.\n");
        }
    }

    return 0;
}
