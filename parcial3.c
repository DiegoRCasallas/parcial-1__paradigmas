#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para almacenar la información de un estudiante
typedef struct {
    char *nombre;
    char *apellido;
    unsigned char edad;  // Utilizamos 1 byte para la edad (0 a 255)
    char id[9];  // El ID será almacenado como una cadena de caracteres fija de 8 caracteres + '\0'
    int *calificaciones;  // Array dinámico para almacenar las calificaciones
    size_t num_calificaciones;  // Tamaño del array dinámico
} Estudiante;
//Lista de estudiantes
typedef struct {
    Estudiante **estudiantes;  // Array dinámico de punteros a estudiantes
    size_t num_estudiantes;  // Número actual de estudiantes
} ListaEstudiantes;
//funcion para iniciar la lista
ListaEstudiantes* crearListaEstudiantes() {
    ListaEstudiantes *lista = (ListaEstudiantes*)malloc(sizeof(ListaEstudiantes));
    lista->estudiantes = NULL;
    lista->num_estudiantes = 0;
    return lista;
}
//funcion para calcular la memoria usada
size_t calcularMemoriaEstudiante(Estudiante *estudiante) {
    size_t memoria_usada = sizeof(Estudiante);  // Tamaño de la estructura base
    
    // Sumar la memoria usada por el nombre y apellido
    memoria_usada += strlen(estudiante->nombre) + 1;  // +1 para el '\0'
    memoria_usada += strlen(estudiante->apellido) + 1;
    
    // Sumar la memoria usada por las calificaciones
    memoria_usada += estudiante->num_calificaciones * sizeof(int);
    
    return memoria_usada;
}
//funcion para crear un estudiante
Estudiante* agregarEstudiante(const char *nombre, const char *apellido, unsigned char edad, const char *id, const int *calificaciones, size_t num_calificaciones) {
    // Asignar memoria para un nuevo estudiante
    Estudiante *nuevo_estudiante = (Estudiante*)malloc(sizeof(Estudiante));

    // Asignar memoria para el nombre y copiar la cadena
    nuevo_estudiante->nombre = (char*)malloc(strlen(nombre) + 1);  // strlen + 1 para el terminador '\0'
    strcpy(nuevo_estudiante->nombre, nombre);

    // Asignar memoria para el apellido y copiar la cadena
    nuevo_estudiante->apellido = (char*)malloc(strlen(apellido) + 1);
    strcpy(nuevo_estudiante->apellido, apellido);

    // Asignar edad
    nuevo_estudiante->edad = edad;

    // Copiar el ID
    strncpy(nuevo_estudiante->id, id, 8);
    nuevo_estudiante->id[8] = '\0';  // Asegurarse de que la cadena termine en '\0'

    // Asignar memoria para el array de calificaciones
    nuevo_estudiante->calificaciones = (int*)malloc(num_calificaciones * sizeof(int));
    memcpy(nuevo_estudiante->calificaciones, calificaciones, num_calificaciones * sizeof(int));
    nuevo_estudiante->num_calificaciones = num_calificaciones;

    return nuevo_estudiante;
}
//funcion para meter a un estudiente a la lista
void agregarEstudianteALista(ListaEstudiantes *lista, Estudiante *nuevo_estudiante) {
    lista->estudiantes = (Estudiante**)realloc(lista->estudiantes, (lista->num_estudiantes + 1) * sizeof(Estudiante*));
    lista->estudiantes[lista->num_estudiantes] = nuevo_estudiante;
    lista->num_estudiantes++;
    
    // Calcular y mostrar la memoria utilizada por el nuevo estudiante
    size_t memoria_usada = calcularMemoriaEstudiante(nuevo_estudiante);
    printf("Estudiante \"%s %s\" agregado correctamente. Memoria utilizada: %zu bytes.\n",
           nuevo_estudiante->nombre, nuevo_estudiante->apellido, memoria_usada);
}
//funcion para eliminar un estudiente y liberar memoria
void eliminarEstudiante(Estudiante *estudiante) {
    if (estudiante) {
        free(estudiante->nombre);
        free(estudiante->apellido);
        free(estudiante->calificaciones);
        free(estudiante);
    }
}
//funcion para buscar el estudiente a eliminar
void eliminarEstudiantePorID(ListaEstudiantes *lista, const char *id) {
    for (size_t i = 0; i < lista->num_estudiantes; i++) {
        if (strcmp(lista->estudiantes[i]->id, id) == 0) {
            // Calcular la memoria usada por el estudiante que se eliminará
            size_t memoria_usada = calcularMemoriaEstudiante(lista->estudiantes[i]);
            
            // Liberar la memoria del estudiante
            eliminarEstudiante(lista->estudiantes[i]);
            
            // Desplazar los elementos restantes del array
            for (size_t j = i; j < lista->num_estudiantes - 1; j++) {
                lista->estudiantes[j] = lista->estudiantes[j + 1];
            }
            
            // Reducir el tamaño del array
            lista->num_estudiantes--;
            lista->estudiantes = (Estudiante**)realloc(lista->estudiantes, lista->num_estudiantes * sizeof(Estudiante*));
            
            printf("Estudiante con ID %s eliminado correctamente. Memoria liberada: %zu bytes.\n", id, memoria_usada);
            return;
        }
    }
    printf("Estudiante con ID %s no encontrado.\n", id);
}
//funcion actualizar a un estudiente y reestructuracion de memoria
void actualizarEstudiante(Estudiante *estudiante, const char *nuevo_nombre, const char *nuevo_apellido, unsigned char nueva_edad, const char *nuevo_id) {
    // Actualizar nombre
    free(estudiante->nombre);
    estudiante->nombre = (char*)malloc(strlen(nuevo_nombre) + 1);
    strcpy(estudiante->nombre, nuevo_nombre);

    // Actualizar apellido
    free(estudiante->apellido);
    estudiante->apellido = (char*)malloc(strlen(nuevo_apellido) + 1);
    strcpy(estudiante->apellido, nuevo_apellido);

    // Actualizar edad
    estudiante->edad = nueva_edad;

    // Actualizar ID
    strncpy(estudiante->id, nuevo_id, 8);
    estudiante->id[8] = '\0';
}
//funcion que muestra los datos de un estudiente
void mostrarEstudiante(Estudiante *estudiante) {
    printf("Nombre: %s %s\n", estudiante->nombre, estudiante->apellido);
    printf("Edad: %u\n", estudiante->edad);
    printf("ID: %s\n", estudiante->id);
    printf("Calificaciones: ");
    for (size_t i = 0; i < estudiante->num_calificaciones; i++) {
        printf("%d ", estudiante->calificaciones[i]);
    }
    printf("\n");
}

int main() {
    // Crear una lista de estudiantes
    ListaEstudiantes *lista = crearListaEstudiantes();
    
    // Crear estudiantes y agregarlos a la lista
    int calificaciones1[] = {85, 90, 78};
    Estudiante *carlos = agregarEstudiante("Carlos", "Gomez", 20, "12345678", calificaciones1, 3);
    agregarEstudianteALista(lista, carlos);
    
    int calificaciones2[] = {75, 88, 92};
    Estudiante *ana = agregarEstudiante("Ana", "Perez", 21, "87654321", calificaciones2, 3);
    agregarEstudianteALista(lista, ana);
    
    // Mostrar estudiantes en la lista
    printf("Estudiantes actuales:\n");
    for (size_t i = 0; i < lista->num_estudiantes; i++) {
        mostrarEstudiante(lista->estudiantes[i]);
    }
    
    // Eliminar un estudiante por ID
    eliminarEstudiantePorID(lista, "12345678");
    
    // Mostrar estudiantes restantes
    printf("\nEstudiantes restantes:\n");
    for (size_t i = 0; i < lista->num_estudiantes; i++) {
        mostrarEstudiante(lista->estudiantes[i]);
    }
    
    // Liberar memoria de los estudiantes restantes
    for (size_t i = 0; i < lista->num_estudiantes; i++) {
        eliminarEstudiante(lista->estudiantes[i]);
    }
    
    // Liberar la lista
    free(lista->estudiantes);
    free(lista);
    
    return 0;
}