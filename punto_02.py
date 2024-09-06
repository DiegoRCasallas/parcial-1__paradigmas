
lista_estudiantes = [
    ("Juanki", 85),
    ("Ana", 92),
    ("Pedro", 85),
    ("Maria", 92),
    ("Luis", 78),
    ("Diego", 99),
    ("Pacheco",65)
]

def bubble_sort(lista):
    n = len(lista)
    for i in range(n):
        for j in range(0, n - i - 1):
            #recoremos la lista estudiantes y accedemos al al nota con [1]
            #comparamos la nota de las listas
            if lista[j][1] < lista[j + 1][1]:
                #usamos una variable auxiliar que nos permita guadar temporalmente un valor
                #que será usado para modificar la posicion de la lista[j]
                aux=lista[j + 1]
                lista[j + 1]= lista[j]
                lista[j]=aux
             # comparamos por nombre usandon el operador >
            elif lista[j][1] == lista[j + 1][1] and lista[j][0] > lista[j + 1][0]:
                aux=lista[j + 1]
                lista[j + 1]= lista[j]
                lista[j]=aux
bubble_sort(lista_estudiantes)
print("Lista de estudiantes ordenada :")
for estudiante in lista_estudiantes:
    print(estudiante)
