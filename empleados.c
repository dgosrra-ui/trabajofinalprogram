#include <stdio.h>
#include <string.h>
#include "empleados.h"


void limpiarSaltoLinea(char *cadena) {
    int len = strlen(cadena);
    while (len > 0 && (cadena[len-1] == '\n' || cadena[len-1] == ' ' || cadena[len-1] == '\r')) 
        cadena[--len] = '\0';
}

int esAlfanumericoSinEspacios(const char *cadena) {
    if (strlen(cadena) == 0) return 0;
    for (int i = 0; cadena[i]; i++) {
        char c = cadena[i];
        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
            return 0;
    }
    return 1;
}

int esCodigoUnico(Empleado empleados[], int cantidad, const char *codigo) {
    for (int i = 0; i < cantidad; i++)
        if (strcmp(empleados[i].codigo, codigo) == 0) return 0;
    return 1;
}



void registrarEmpleado(Empleado empleados[], int *cantidad) {
    if (*cantidad >= MAX_EMPLEADOS) {
        printf("\n Error: Límite máximo de empleados alcanzado.\n");
        return;
    }

    Empleado nuevo;
    char buffer[100];
    printf("\n=== Registrar Nuevo Empleado ===\n");

    do {
        printf("Código de empleado (1-15 caracteres, sin espacios): ");
        fgets(nuevo.codigo, sizeof(nuevo.codigo), stdin);
        limpiarSaltoLinea(nuevo.codigo);
        if (!esAlfanumericoSinEspacios(nuevo.codigo)) {
            printf(" Código inválido. Alfanumérico sin espacios.\n");
        } else if (!esCodigoUnico(empleados, *cantidad, nuevo.codigo)) {
            printf(" El código ya existe. Intente otro.\n");
        } else break;
    } while (1);

    printf("Nombre completo: ");
    fgets(nuevo.nombre, sizeof(nuevo.nombre), stdin);
    limpiarSaltoLinea(nuevo.nombre);

    printf("Cargo: ");
    fgets(nuevo.cargo, sizeof(nuevo.cargo), stdin);
    limpiarSaltoLinea(nuevo.cargo);

    do {
        printf("Sueldo base (> 0): ");
        if (sscanf(fgets(buffer, sizeof(buffer), stdin), "%f", &nuevo.sueldoBase) != 1 || nuevo.sueldoBase <= 0)
            printf(" Inválido. Número mayor que 0.\n");
        else break;
    } while (1);

    do {
        printf("Horas extra (>= 0): ");
        if (sscanf(fgets(buffer, sizeof(buffer), stdin), "%d", &nuevo.horasExtra) != 1 || nuevo.horasExtra < 0)
            printf(" Inválido. Número entero >= 0.\n");
        else break;
    } while (1);

    empleados[(*cantidad)++] = nuevo;
    printf("\n Empleado registrado con éxito.\n");
}

void buscarEmpleado(Empleado empleados[], int cantidad) {
    if (cantidad == 0) {
        printf("\n No hay empleados registrados.\n");
        return;
    }

    char criterio[100];
    int encontrados = 0;

    printf("\n=== Buscar Empleado ===\n");
    printf("Ingrese código o parte del nombre: ");
    fgets(criterio, sizeof(criterio), stdin);
    limpiarSaltoLinea(criterio);

    printf("\n%-15s %-25s %-20s %-12s %-12s %-12s\n", 
           "Código", "Nombre", "Cargo", "Sueldo Base", "Hrs Extra", "Sueldo Total");
    printf("-----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < cantidad; i++) {
        if (strcmp(empleados[i].codigo, criterio) == 0 || strstr(empleados[i].nombre, criterio) != NULL) {
            float sueldoTotal = calcularSueldoTotal(empleados[i]);
            printf("%-15s %-25s %-20s $%-11.2f %-12d $%-11.2f\n", 
                   empleados[i].codigo, empleados[i].nombre, empleados[i].cargo, 
                   empleados[i].sueldoBase, empleados[i].horasExtra, sueldoTotal);
            encontrados++;
        }
    }

    printf("-------------------\n");
    if (encontrados == 0) printf(" Sin resultados.\n");
}

void actualizarEmpleado(Empleado empleados[], int cantidad) {
    if (cantidad == 0) {
        printf("\n No hay empleados para actualizar.\n");
        return;
    }

    char codigoBuscado[16], buffer[100];
    int indice = -1;

    printf("\n=== Actualizar Empleado ===\n");
    printf("Código del empleado: ");
    fgets(codigoBuscado, sizeof(codigoBuscado), stdin);
    limpiarSaltoLinea(codigoBuscado);

    for (int i = 0; i < cantidad; i++) {
        if (strcmp(empleados[i].codigo, codigoBuscado) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf(" Empleado '%s' no encontrado.\n", codigoBuscado);
        return;
    }

    printf("\nModificando: %s - %s\n", empleados[indice].codigo, empleados[indice].nombre);
    printf("(ENTER para mantener valor actual)\n\n");

    printf("Nombre [%s]: ", empleados[indice].nombre);
    fgets(buffer, sizeof(buffer), stdin);
    limpiarSaltoLinea(buffer);
    if (strlen(buffer) > 0) strcpy(empleados[indice].nombre, buffer);

    printf("Cargo [%s]: ", empleados[indice].cargo);
    fgets(buffer, sizeof(buffer), stdin);
    limpiarSaltoLinea(buffer);
    if (strlen(buffer) > 0) strcpy(empleados[indice].cargo, buffer);

    do {
        printf("Sueldo base [$%.2f]: ", empleados[indice].sueldoBase);
        if (fgets(buffer, sizeof(buffer), stdin) && strlen(buffer) > 1) {
            float nuevoSueldo;
            if (sscanf(buffer, "%f", &nuevoSueldo) == 1 && nuevoSueldo > 0) {
                empleados[indice].sueldoBase = nuevoSueldo;
                break;
            }
            printf(" Número > 0.\n");
        } else break;
    } while (1);

    do {
        printf("Horas extra [%d]: ", empleados[indice].horasExtra);
        if (fgets(buffer, sizeof(buffer), stdin) && strlen(buffer) > 1) {
            int nuevasHoras;
            if (sscanf(buffer, "%d", &nuevasHoras) == 1 && nuevasHoras >= 0) {
                empleados[indice].horasExtra = nuevasHoras;
                break;
            }
            printf(" Número >= 0.\n");
        } else break;
    } while (1);

    printf("\n Datos actualizados.\n");
}