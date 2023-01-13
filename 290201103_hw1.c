#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 2

typedef struct song
{
    char *name;
    float duration;
} song;

typedef struct dynamic_array
{
    int capacity;
    int size;
    void **elements;
} dynamic_array;

dynamic_array arr;

void increaseCapacity(dynamic_array *array);                 // increase the capacity when capacity = size
void decreaseCapacity(dynamic_array *array);                 // decrease the capacity when capacity/2 = size
void listAll(dynamic_array *array);                          // list all elements using get_element method
int getPositionByName(dynamic_array *array, char *songName); // get position in dynamic_array by name
void init_array(dynamic_array *array);                       // initializing
void put_element(dynamic_array *array, void *element);       // put element in dynamic_array
void remove_element(dynamic_array *array, int position);     // remove element in dynamic_array
void *get_element(dynamic_array *array, int position);       // get element by position
song *getSongFromUser();                                     // get song input from the user

void init_array(dynamic_array *array)
{
    array->capacity = INITIAL_CAPACITY;
    array->size = 0;
    array->elements = malloc(array->capacity * sizeof(void *));
    array->elements[0] = NULL;
    array->elements[1] = NULL;
}
void put_element(dynamic_array *array, void *element)
{
    if (array != NULL)
    {
        if (array->capacity == array->size)
            increaseCapacity(array);
        if (array->elements[array->size] == NULL)
        {
            array->elements[array->size] = element;
            (array->size)++;
        }
    }
    else
    {
        init_array(array);
    }
}

void remove_element(dynamic_array *array, int position)
{
    if (array != NULL)
    {
        free(get_element(array, position));
        for (int i = position; i < array->size; i++)
        {
            array->elements[i] = array->elements[i + 1];
        }
        (array->size)--;
        if (array->capacity / 2 == array->size)
            decreaseCapacity(array);
    }
}
void *get_element(dynamic_array *array, int position)
{
    return array->elements[position];
}

void increaseCapacity(dynamic_array *array)
{
    array->capacity *= 2;
    void **new_elements = malloc(array->capacity * sizeof(void *));
    for (int i = 0; i < array->capacity; i++)
    {
        if (i < array->size)
            new_elements[i] = array->elements[i];
        else
            new_elements[i] = NULL;
    }
    free(array->elements);
    array->elements = new_elements;
}

void decreaseCapacity(dynamic_array *array)
{
    array->capacity = array->size;
    void **new_elements = malloc(array->capacity * sizeof(void *));
    for (int i = 0; i < array->capacity; i++)
    {
        new_elements[i] = array->elements[i];
    }
    free(array->elements);
    array->elements = new_elements;
}

void listAll(dynamic_array *array)
{
    printf("Index\tSong Name\tSong Duration\n");
    printf("-----\t-----------\t--------------\n");
    for (int i = 0; i < array->size; i++)
    {
        song *song_ptr = (song *)get_element(array, i);
        printf("%d\t%s\t\t%.2f\n", (i + 1), song_ptr->name, song_ptr->duration);
    }
}
int getPositionByName(dynamic_array *array, char *songName)
{
    if (array != NULL)
    {
        for (int i = 0; i < array->size; i++)
        {
            struct song *song = (struct song *)array->elements[i];
            if (!strcmp(song->name, songName))
            {
                return i;
            }
        }
        return -1;
    }
}

song *getSongFromUser()
{
    song *song = malloc(sizeof(void *));
    song->name = malloc(sizeof(void *));
    printf("Enter your song name: \n");
    scanf("%s", song->name);
    printf("Enter your song's duration: \n");
    scanf("%f", &song->duration);

    return song;
}

int main()
{
    init_array(&arr);

    printf("\n\tSONG LIST APPLICATION");
    printf("\n\t-----------------------\n");
    int choice = 0;
    while (choice != 4)
    {

        printf("\nPlease choose one of the option.\n\n");
        printf("1. Add a Song\n");
        printf("2. Delete the Song\n");
        printf("3. List the Song\n");
        printf("4. Exit\n");

        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            put_element(&arr, getSongFromUser());
            break;
        case 2:
            char *songName = malloc(sizeof(void *));
            printf("\nPlease enter the song name to remove:\n");
            scanf("%s", songName);
            int position = getPositionByName(&arr, songName);
            if (position == -1)
            {
                printf("There is no such song!");
            }
            else
            {
                remove_element(&arr, position);
            }

            break;
        case 3:
            listAll(&arr);
            break;
        case 4:
            printf("\n\n See You...\n");
            break;
        default:
            printf("\n\nINVALID SELECTION...Please try again\n");
        }
    }
    return 0;
}
