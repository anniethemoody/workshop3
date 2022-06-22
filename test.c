
Node * makeNode (char *insertSongName, char *insertArtist, char *insertingGenre);
Node *insertNode (Node *head, Node * inputNode);
void printMusic (Node * node);
void printLibrary (Node * head);
void search (Node * head, char *SongName);
Node *deletingSong (Node *head, char *SongName);
Node *deletingLibrary (Node * head);

int main(void) {
  // Declare the head of the linked list. 
  //   ADD YOUR STATEMENT(S) HERE
    Node * head = NULL;

  // Announce the start of the program
  printf("Personal Music Library.\n\n");
  printf("%s", "Commands are I (insert), D (delete), S (search by song name),\n"
               "P (print), Q (quit).\n");

  char response;
  char input[MAX_LENGTH + 1];

  do {
    inputStringFromUser("\nCommand", input, MAX_LENGTH);

    // Response is the first character entered by user.
    // Convert to uppercase to simplify later comparisons.
    response = toupper(input[0]);

    if (response == 'I') {
      // Insert a song into the linked list.
      // Maintain the list in alphabetical order by song name.
      //   ADD STATEMENT(S) HERE
      // USE THE FOLLOWING STRINGS WHEN PROMPTING FOR DATA:
        char declareSongName [MAX_LENGTH + 1];
        char declareArtist [MAX_LENGTH + 1];
        char declareGenre [MAX_LENGTH + 1];
       
        char *promptName = "Song name";
        char *promptArtist = "Artist";
        char *promptGenre = "Genre";

        inputStringFromUser(promptName, declareSongName, MAX_LENGTH);
        inputStringFromUser(promptArtist, declareArtist, MAX_LENGTH);
        inputStringFromUser(promptGenre, declareGenre, MAX_LENGTH);
        
        //calling the inserting node
        head = insertNode (head, makeNode (declareSongName, declareArtist, declareGenre));

    } else if (response == 'D') {
      // Delete a song from the list.

      char *prompt = "\nEnter the name of the song to be deleted";
      //   ADD STATEMENT(S) HERE;
      char inputDeleteSong [MAX_LENGTH + 1];
      inputStringFromUser (prompt, inputDeleteSong, MAX_LENGTH);
      head = deletingSong (head, inputDeleteSong);

    } else if (response == 'S') {
      // Search for a song by its name.

      char *prompt = "\nEnter the name of the song to search for";
      //   ADD STATEMENT(S) HERE
      char searchInputSong [MAX_LENGTH +1];
      inputStringFromUser (prompt, searchInputSong, MAX_LENGTH);
      search (head, searchInputSong);


    } else if (response == 'P') {
      // Print the music library.
      //   ADD STATEMENT(S) HERE
      printLibrary (head);

    } else if (response == 'Q') {
      ; // do nothing, we'll catch this below
    } else {
      // do this if no command matched ...
      printf("\nInvalid command.\n");
    }
  } while (response != 'Q');

  // Delete the entire linked list.
  //   ADD STATEMENT(S) HERE

  // Print the linked list to confirm deletion.
  //   ADD STATEMENT(S) HERE
    head = deletingLibrary (head);

  return 0;
}

// Support Function Definitions



// Function to call when a song name that is to be deleted




// Add your functions below this line.

//   ADD STATEMENT(S) HERE

//function to create the node
Node * makeNode (char *insertSongName, char *insertArtist, char *insertingGenre){
    Node * newNode;
    newNode = (struct node *) malloc (sizeof (struct node));

    if (newNode != NULL){
      //allocate memory for the strings entered
      //+1 due to the null terminator 
      newNode -> songName = (char *) malloc (sizeof (strlen (insertSongName) + 1));
      newNode -> artist = (char *) malloc (sizeof (strlen (insertArtist) + 1));
      newNode -> genre = (char *) malloc (sizeof (strlen (insertingGenre) + 1)); 
  

        strcpy (newNode -> songName, insertSongName);
        strcpy (newNode -> artist, insertArtist);
        strcpy (newNode -> genre, insertingGenre);
        newNode -> next = NULL;
    }
    return newNode;
}

//function to add the node 
//reads song name 
//reads artist
//reads genre of the song
//sort the song directly 
Node *insertNode (Node *head, Node * inputNode){
    Node * prev = NULL;
    Node * curr = head;

    while (curr != NULL && strcmp (inputNode -> songName, curr -> songName) > 0){
      prev = curr;
      curr = curr -> next;
    }
    if (curr != NULL && strcmp (curr -> songName, inputNode -> songName) == 0){
      songNameDuplicate (inputNode -> songName);
      free (inputNode -> songName);
      free (inputNode -> artist);
      free (inputNode -> genre);
      free (inputNode);
    }
    else {
      inputNode -> next = curr;

      if (prev == NULL){
        head = inputNode;
      }
      else {
        prev -> next = inputNode;
      }
    }
    
    return head;
}


void printMusic (Node * node){
    printf ("\n%s", node -> songName);
    printf ("\n%s", node -> artist);
    printf ("\n%s\n", node -> genre);
}

//printing the library for command P 
void printLibrary (Node * head){
    Node * temp = head;
    
    //if there is nothing in the library
    if (temp == NULL){
      printMusicLibraryEmpty ();
      return;
    }
    printMusicLibraryTitle ();
    Node * currentNode = temp;
    
    //check if currentNode != NULL
    //print currentNode = songName
    //printMusic (currentNode);
    while (currentNode != NULL){
        printMusic (currentNode);
        currentNode = currentNode -> next;
    }
}

//delete
//find if item exists
//previous item, point to current -> next
//free current 
// head -> a-> b -> c
//delete at head, delete at end, delete in the middle
//if delete at head (a), head will point to b and a will point to null or free
//if delete at middle, a will point at c and free b.
//if delete at end, b points to null and free c.

void search (Node *head, char *SongName){
  while (head != NULL){
    if (strcmp (head -> songName, SongName) == 0){
      songNameFound(SongName);
      printMusic (head);
      return;
     }
    //if song name is not found in the library
    head = head -> next;
  }
   songNameNotFound (SongName);
   return;
} 

Node *deletingSong (Node *head, char *SongName){
  Node * curr = head; 
  Node * prev = NULL;

  while (curr != NULL && strcmp (curr -> songName, SongName) != 0){
    prev = curr;
    curr = curr -> next; 
  }
  if (curr == NULL){
    songNameNotFound (SongName);
  }  
  if (curr != NULL){
    if (prev == NULL){
      head = curr -> next;
    }
    else {
      prev -> next = curr -> next;
    }
    songNameDeleted (SongName);
      free (curr -> songName);
      free (curr -> artist);
      free (curr -> genre);
      free (curr);
  }
  return head;
}

//for command Q
//as long as head is not equal to null, delete first item, then second, then third until empty.
// may use while loop 
Node *deletingLibrary (Node * head){
  Node *temp = head;

  while (head != NULL){
    songNameDeleted (head -> songName);
    temp = head;
    head = head -> next;
    free (temp -> songName);
    free (temp -> artist);
    free (temp -> genre);
    free (temp);
  }
  printMusicLibraryEmpty ();

  return head;
}
