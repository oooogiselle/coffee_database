#include <stdio.h>
#include <string.h>
#define MAX 500

typedef struct {
  char name[MAX];
  char roast[MAX];
  char origin[MAX];
  float g_USD;
  int rating;
} coffee;

void readFile(coffee *ptr, int *SIZE);
void displayData(coffee Espresso[], int *SIZE);
void searchData(coffee Espresso[], int *SIZE);
void sortData(coffee *ptr, int *SIZE);
void addData(coffee *ptr, int *SIZE);
void deleteData(coffee Espresso[], int *SIZE);
void saveData(coffee *ptr, int *SIZE);
void displayMenu();
void introduceData();

int main(void) {
  int SIZE = 88;
  coffee Espresso[SIZE];
  
  char ch;

  do {
    introduceData();
    printf("\n");
    readFile(Espresso, &SIZE);
    printf("\n");
    printf("\n");
    displayMenu();

    printf("\nEnter choice (S, D, O, A, E, V, Q): ");
    scanf(" %c", &ch);
    printf("You selected option %c\n", ch);

    //menu!
    switch (ch) {
      case 'S':
        searchData(Espresso, &SIZE);
        break;
      case 'D':
        displayData(Espresso, &SIZE);
        break;
      case 'O':
        sortData(Espresso, &SIZE);
        displayData(Espresso, &SIZE);
        break;
      case 'A':
        addData(Espresso, &SIZE);
        displayData(Espresso, &SIZE);
        break;
      case 'E':
        deleteData(Espresso, &SIZE);
        displayData(Espresso, &SIZE);
        break;
      case 'V':
        saveData(Espresso, &SIZE);
        break;
      case 'Q':
        printf("Exiting...\n");
        break;
      default:
        printf("Invalid option\n");
        break;
    }
  } while (ch != 'Q'); 

  
  return 0;
}

void introduceData(){
  printf("Welcome to the coffee data set!☕\n");
  printf("\n");
  printf("The data used in this data set is scaped using python from the website www.coffeereview.com. \n");
  printf("\n");
  printf("It is a cleaned and pre-processed version with standardized prices, simplified country locations, and reduced number of features\n");
  printf("\n");
  printf("This data set tells you the name, type of roast, origin, price per 100 grams, and rating of the coffee!\n");
 
}

void displayMenu(){
  printf("  [S]earch Data\n");
  printf("  [D]isplay Data\n");
  printf(" S[O]rt Data\n");
  printf("  [A]dd Data\n");
  printf(" D[E]lete Data\n");
  printf("Sa[V]e Data\n");
  printf("  [Q]uit\n");

}

void readFile(coffee *ptr, int *SIZE){
  FILE *ifile;
  int num = 0;
  char fileName[MAX], ch;

  //asks the user to enter filename or use default file
  printf("Please enter file name to open or enter 'd' to open default file: ");
  scanf(" %s", fileName);
  
  if (strcmp("d", fileName) == 0){
    ifile = fopen("simplified_coffee.txt", "r");
    printf("\nOpening default file...\n");
  } else {
    ifile = fopen(fileName, "r");
    printf("\nOpening %s...\n", fileName);
  }

  //checks if file exists
  if(ifile == NULL){
    printf("Error: unable to open file");
    return;
  }

  //reads the file
  while (fscanf(ifile, "%[^,],%[^,],%[^,],%f,%d\n", ptr[num].name, ptr[num].roast, ptr[num].origin, &ptr[num].g_USD, &ptr[num].rating) == 5 && num < SIZE){
    num++;
    //%[^,] reads until a comma, help from TA hours 
  }
 
  fclose(ifile);
}

void searchData(coffee Espresso[], int *SIZE){
  char ch;
  char name[MAX], roast[MAX], origin[MAX];
  int rating, i, found, searchSize;
  float g_USD;
  coffee searchEspresso[MAX];

  do {
    printf("Search [n]ame\n");
    printf("Search ro[a]st\n");
    printf("Search [o]rigin\n");
    printf("Search [g]_USD\n");
    printf("Search [r]ating\n");
    printf("[q]uit\n");

    printf("Enter choice (n,a,o,g,r,q): ");
    scanf(" %c", &ch);

    printf("You selected option %c\n", ch);

    switch(ch){
      //search for name
      case 'n':
        printf("Enter the name you are searching for: ");
        scanf(" %[^\n]", name);
        printf("Searching for: %s\n", name);
        printf("\n");
        searchSize = 0; 

        found = 0;
        for (i = 0; i < *SIZE; i++) {
          if (strcmp(Espresso[i].name, name) == 0) { 
            strcpy(searchEspresso[searchSize].name, Espresso[i].name);
            strcpy(searchEspresso[searchSize].roast, Espresso[i].roast);
            strcpy(searchEspresso[searchSize].origin, Espresso[i].origin);
            searchEspresso[searchSize].g_USD = Espresso[i].g_USD;
            searchEspresso[searchSize].rating = Espresso[i].rating;
            found = 1; //flag found
            searchSize++; //increase index for searchSize
          }
        }
        if (!found) {
          printf("No match found\n");
        } else{
          displayData(searchEspresso, &searchSize);
          saveData(searchEspresso, &searchSize); //ask if user wants to save data 
        }
        break;
      
      case 'a':
        //search for type of roast 
        printf("Enter the type of roast you are searching for: ");
        scanf(" %[^\n]", roast);
        printf("Searching for: %s\n", roast);
        printf("\n");
        searchSize = 0; 

        found = 0;
        for (i = 0; i < *SIZE; i++) {
          if (strcmp(Espresso[i].roast, roast) == 0) {
            strcpy(searchEspresso[searchSize].name, Espresso[i].name);
            strcpy(searchEspresso[searchSize].roast, Espresso[i].roast);
            strcpy(searchEspresso[searchSize].origin, Espresso[i].origin);
            searchEspresso[searchSize].g_USD = Espresso[i].g_USD;
            searchEspresso[searchSize].rating = Espresso[i].rating;
            found = 1;
            searchSize++;
          }
        }
        if (!found) {
          printf("No match found\n");
        } else{
          displayData(searchEspresso, &searchSize);
          saveData(searchEspresso, &searchSize);
        }
        break;

      case 'o':
        //search for origin
        printf("Enter the origin you are searching for: ");
        scanf(" %[^\n]", origin);
        printf("Searching for: %s\n", origin);
        printf("\n");
        searchSize = 0; 

        found = 0;
        for (i = 0; i < *SIZE; i++) {
          if (strcmp(Espresso[i].origin, origin) == 0) {
            strcpy(searchEspresso[searchSize].name, Espresso[i].name);
            strcpy(searchEspresso[searchSize].roast, Espresso[i].roast);
            strcpy(searchEspresso[searchSize].origin, Espresso[i].origin);
            searchEspresso[searchSize].g_USD = Espresso[i].g_USD;
            searchEspresso[searchSize].rating = Espresso[i].rating;
            found = 1;
            searchSize++;
          }
        }
        if (!found) {
          printf("No match found\n");
        } else{
          displayData(searchEspresso, &searchSize);
          saveData(searchEspresso, &searchSize);
        }
        break;

      case 'g':
        //search for origin
        printf("Enter the price per 100g you are searching for: ");
        scanf(" %f", &g_USD);
        printf("Searching for: %f\n", g_USD);
        printf("\n");
        searchSize = 0;

        found = 0;
        for (i = 0; i < *SIZE; i++) {
          if (Espresso[i].g_USD == g_USD) {
            strcpy(searchEspresso[searchSize].name, Espresso[i].name);
            strcpy(searchEspresso[searchSize].roast, Espresso[i].roast);
            strcpy(searchEspresso[searchSize].origin, Espresso[i].origin);
            searchEspresso[searchSize].g_USD = Espresso[i].g_USD;
            searchEspresso[searchSize].rating = Espresso[i].rating;
            found = 1;
            searchSize++;
          }
        }
        if (!found) {
          printf("No match found\n");
        } else{
          displayData(searchEspresso, &searchSize);
          saveData(searchEspresso, &searchSize);
        }
        break;

      case 'r':
        printf("Enter the rating you are searching for: ");
        scanf(" %d", &rating);
        printf("Searching for: %d\n", rating);
        printf("\n");
        searchSize = 0;

        found = 0;
        for (i = 0; i < *SIZE; i++) {
          if (Espresso[i].rating == rating) {
            strcpy(searchEspresso[searchSize].name, Espresso[i].name);
            strcpy(searchEspresso[searchSize].roast, Espresso[i].roast);
            strcpy(searchEspresso[searchSize].origin, Espresso[i].origin);
            searchEspresso[searchSize].g_USD = Espresso[i].g_USD;
            searchEspresso[searchSize].rating = Espresso[i].rating;
            found = 1;
            searchSize++;
          }
        }
        if (!found) {
          printf("No match found\n");
        } else{
          displayData(searchEspresso, &searchSize);
          saveData(searchEspresso, &searchSize);
        }
        break;

      case 'q':
        //quit
        printf("\nReturning to main menu...\n");
        printf("\n");
        return;

      default:
        printf("Invalid option, please try again.\n"); 
    } 
  } while (1);
}

void displayData(coffee Espresso[], int *SIZE){
  int i;

  printf("|                        Coffee                         |        Roast       |     Origin    | g_USD | Rating |\n");

  printf("-----------------------------------------------------------------------------------------------------------------\n");
 //print header

  for(i = 0; i < *SIZE; i++) {
    printf("|%55s|%20s|%15s|%7.2f|%8d|\n", Espresso[i].name, Espresso[i].roast, Espresso[i].origin, Espresso[i].g_USD, Espresso[i].rating);
  } //print out all the elements within the size 

  printf("-----------------------------------------------------------------------------------------------------------------\n");

}

void sortData(coffee *ptr, int *SIZE){
  char ch1, ch2;
  int i, j; 
  coffee swap;

  printf("Sort by price (low to high): [p1]\n");
  printf("Sort by price (high to low):[p2]\n");
  printf("Sort by rating (low to high):[r1]\n");
  printf("Sort by rating (high to low):[r2]\n");

  printf("Enter choice (p1, p2, r1, r2): ");
  scanf(" %c%c", &ch1, &ch2);


  if (ch1 == 'p' && ch2 == '1'){
    for(i = 0; i < *SIZE; i++){
      for(j = 0; j < *SIZE; j++){
        if (ptr[j].g_USD > ptr[j + 1].g_USD) {
            // Swap entire structure
            swap = ptr[j];
            ptr[j] = ptr[j + 1];
            ptr[j + 1] = swap;
        }
      }
    }
  }

  if (ch1 == 'p' && ch2 == '2'){
    for(i = 0; i < *SIZE; i++){
      for(j = 0; j < *SIZE; j++){
        if (ptr[j].g_USD < ptr[j + 1].g_USD) {
          // Swap entire structure
          swap = ptr[j];
          ptr[j] = ptr[j + 1];
          ptr[j + 1] = swap;
        }
      }
    }
  }

  if (ch1 == 'r' && ch2 == '1'){
    for(i = 0; i < *SIZE; i++){
      for(j = 0; j < *SIZE; j++){
        if (ptr[j].rating > ptr[j + 1].rating) {
          // Swap entire structure
          swap = ptr[j];
          ptr[j] = ptr[j + 1];
          ptr[j + 1] = swap;
        }
      }
    }
  }

  if (ch1 == 'r' && ch2 == '2'){
    for(i = 0; i < *SIZE; i++){
      for(j = 0; j < *SIZE; j++){
        if (ptr[j].rating < ptr[j + 1].rating) {
          // Swap entire structure
          swap = ptr[j];
          ptr[j] = ptr[j + 1];
          ptr[j + 1] = swap;
        }
      }
    }
  } 
}

void addData(coffee *ptr, int *SIZE){
  if (*SIZE < MAX) { //set a limit to the max capacity as 500
    printf("Enter the name of the coffee: ");
    scanf(" %[^\n]", ptr[*SIZE].name);
    printf("Enter the type of roast: ");
    scanf(" %[^\n]", ptr[*SIZE].roast);
    printf("Enter the origin: ");
    scanf(" %[^\n]", ptr[*SIZE].origin);
    printf("Enter the price per 100g: ");
    scanf("%f", &ptr[*SIZE].g_USD);
    printf("Enter the rating: ");
    scanf("%d", &ptr[*SIZE].rating);

    (*SIZE)++; //increase size when 1 record is added 
    printf("Record added successfully.\n");
} else {
    printf("Maximum capacity reached. Cannot add more records.\n");
  }
  
}

void deleteData(coffee *ptr, int *SIZE){
  char name[MAX];
  int i, found;

  printf("Enter the name of the coffee to delete: ");
  scanf(" %[^\n]", name);

  found = 0; //flag

  for (i = 0; i < *SIZE && !found; i++) {
    // when not found keep looping 
    if (strcmp(ptr[i].name, name) == 0) {
      // Found the record to delete
      found = 1;
      // Shift remaining records to the left to overwrite the deleted record
      for (int j = i; j < *SIZE; j++) {
        strcpy(ptr[j].name, ptr[j + 1].name);
        strcpy(ptr[j].roast, ptr[j + 1].roast);
        strcpy(ptr[j].origin, ptr[j + 1].origin);
        ptr[j].g_USD = ptr[j + 1].g_USD;
        ptr[j].rating = ptr[j + 1].rating;
      }
      (*SIZE)--; //SIZE decreases
      printf("Record deleted successfully.\n");
     
    }
  }

  if (!found) {
    printf("Record with name '%s' not found.\n", name);
  }
  
}

void saveData(coffee *ptr, int *SIZE){
  FILE *ifile;
  char ch, ch2, junk;
  char fileName[MAX];
  int i;
  
  printf("Do you wish to save data? (y, n): ");
  scanf(" %c", &ch);
  scanf("%c", &junk);

  if(ch == 'y'){
    printf("Name your file: ");
    scanf("%s", fileName); //name file
    
    if(strcmp(fileName, "simplified_coffee.txt") == 0){
      printf("File already existed. Do you wish to overwrite an existing file? (y,n): ");
      scanf(" %c", &ch2);
      if (ch2 == 'n'){
        printf("File not saved.\n");
      } 
    }

    ifile = fopen(fileName, "w");
    if (ifile == NULL) {
      printf("Error: Unable to open file.\n");
    } 
    
    for(i = 0; i < *SIZE; i++){
      fprintf(ifile, "%s, %s, %s, %.2f, %d\n", ptr[i].name, ptr[i].roast, ptr[i].origin, ptr[i].g_USD, ptr[i].rating);  
    }
    
    fclose(ifile);
    printf("Data successfully saved.\n");
    
  } else {
    printf("File not saved.\n");
  }
}
