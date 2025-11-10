#include <stdio.h>
#include <stdlib.h>

/*
   tree.c
   Ejemplo simple de árbol binario de búsqueda (BST) en C.
   El código está comentado en español y explica paso a paso las operaciones.
*/

/* 1) Estructura del nodo */
struct Node {
    int key;               // Valor almacenado en el nodo
    struct Node *left;     // Puntero al hijo izquierdo
    struct Node *right;    // Puntero al hijo derecho
};

/* 2) Crear un nuevo nodo (reserva memoria y asigna valores) */
struct Node* create_node(int key) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    if (node == NULL) {
        fprintf(stderr, "Error: memoria insuficiente\n");
        exit(EXIT_FAILURE);
    }
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/* 3) Insertar una clave en el árbol BST */
struct Node* insert(struct Node* root, int key) {
    if (root == NULL) {
        return create_node(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else {
        root->right = insert(root->right, key);
    }

    return root;
}

/* 4) Buscar una clave en el BST */
struct Node* search(struct Node* root, int key) {
    if (root == NULL) return NULL;
    if (key == root->key) return root;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}

/* 5) Recorridos del árbol */

// Inorder descendente (mayor a menor)
void inorder(struct Node* root) {
    if (root == NULL) return;
    inorder(root->right);
    printf("%d ", root->key);
    inorder(root->left);
}

// Preorder
void preorder(struct Node* root) {
    if (root == NULL) return;
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

// Postorder
void postorder(struct Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
}

/* 6) Liberar memoria del árbol */
void free_tree(struct Node* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

/* 7) Función main */
int main(void) {
    struct Node* root = NULL; // Árbol vacío

    int n; // cantidad de números que ingresará el usuario
    printf("¿Cuántos números desea insertar en el árbol?: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Debe ingresar al menos un número.\n");
        return 0;
    }

    printf("Ingrese los %d números separados por espacio o salto de línea:\n", n);
    for (int i = 0; i < n; ++i) {
        int value;
        scanf("%d", &value);
        root = insert(root, value);
    }

    // Mostrar recorridos
    printf("\n--- Recorridos del árbol ---\n");
    printf("Inorder (orden descendente): ");
    inorder(root);
    printf("\n");

    printf("Preorder: ");
    preorder(root);
    printf("\n");

    printf("Postorder: ");
    postorder(root);
    printf("\n");

    // Ejemplo de búsqueda (opcional)
    int to_find;
    printf("\nIngrese un valor para buscar en el árbol: ");
    scanf("%d", &to_find);

    struct Node* found = search(root, to_find);
    if (found != NULL) {
        printf("Clave %d encontrada en el árbol.\n", to_find);
    } else {
        printf("Clave %d NO encontrada en el árbol.\n", to_find);
    }

    // Liberar memoria
    free_tree(root);
    root = NULL;

    printf("\nMemoria liberada correctamente. Fin del programa.\n");
    return 0;
}
