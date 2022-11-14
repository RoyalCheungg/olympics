#include <stdlib.h>
#include <stdio.h>
#define MAXEVENTS 99 // REMEMBER TO UDATE THIS TO 99

int numEvents = -1;

// creating a linked list FOR EVENTS

struct event
{
    int eventCode; 
    char eventName [100] ;
    int numCompetitors;
    char gender[1];
    struct event *next; 
};

// creating a linked list for ATHLETES

struct athlete
{
    int athleteCode; 
    char athleteName [100];
    int athleteAge;
    char athleteGender[1];
    struct athlete *next; 
};

// creating a new variable eventDB that will be a pointer to the first node in the list 

struct event *eventDB = NULL; 

struct event *findEvent(int eventNumber); 

// creating a new variable athleteDB that will be a pointer to the first node in the list 

struct athlete *athleteDB = NULL; 

struct athlete *findAthlete(int athleteNumber);


// readline function to skip whitespace char 

int readline(char str[], int n){
    int ch, i = 0;
    while (isspace(ch = getchar()));
    while (ch != '\n' && ch != EOF) 
    {
        if (i < n)
        str[i++] = ch;
        ch = getchar();
    }
    str[i] = '\0';
    return i;
}

// creating a findEvent structure function 
struct event *findEvent(int eventNumber)
{
    struct event *new; 
    for(new = eventDB; new != NULL && eventNumber > new->eventCode; new = new->next); 
    if(new != NULL && eventNumber == new->eventCode)
    {
        return new; 
    }
    return NULL; 
}

// creating a findAthlete structure function 

// creating a findEvent structure function 

struct athlete *findAthlete(int athleteNumber)
{
    struct athlete *new; 
    for(new = athleteDB; new != NULL && athleteNumber > new->athleteCode; new = new->next); 
    if(new != NULL && athleteNumber == new->athleteCode)
    {
        return new; 
    }
    return NULL; 
}

// main function for the Winter 2022 Database

int main()
{
    // initializing the current variables 
    
    char str1;
    char str2; 
    int eventCode;
    char eventName[100];
    int numCompetitors;
    char gender[1];
    char athleteGender[1];
    int athleteAge;
    
    printf("************************** \n 2211 Winter Olympics!\n**************************");
    
    // if the user enters q, program will stop 
    
    for (;;) 
    {
        printf("\nEnter entity type (h for help, q to quit, e for events, a for athletes): \n");
        scanf(" %c", &str2);
        while (getchar() != '\n')   /* skips to end of line */
        ;
        
        if (str2 == 'h')
        {
            printf("\nEnter e for event, a for athlete, then\n");
            printf("Enter operation code: i to insert, s to search,\n\tu to update, p to print\n ");
        }

        if (str2 == 'e')
        { 
            printf("\nEnter operation code: \n 'i' to input \n 's' to search \n 'u' to update \n 'p' to print \n 'q' to quit\n"); 
                // take in user input 
                scanf("%c", &str1); 
                
                switch(str1)
                {
                    // program will allow user to enter a new event name
                    
                // ======= case i, EVENT insert ======== // 
                    case 'i':
                    {       
                        
                        struct event *curEvent, *prevEvent, *newEvent; 
                        newEvent = malloc(sizeof(struct event)); 

                        // check if the database is full 
                        if(newEvent == NULL)
                        {
                            printf("\nThe database is full\n"); 
                            return 0; 
                        }

                        // if not full then do this 
                        printf("\nEnter the Event code: \n"); 
                        scanf("%d", &newEvent->eventCode); 


                        for(curEvent = eventDB, prevEvent = NULL; curEvent != NULL && newEvent->eventCode > curEvent->eventCode; prevEvent = curEvent, curEvent = curEvent->next); 

                        if(curEvent != NULL && newEvent->eventCode == curEvent->eventCode)
                        {
                            printf("\nThe event code already exists\n");
                            free(newEvent);
                            return 0; 
                        } 
 

                        printf("\nEnter the event name: \n"); 
                        readline(newEvent->eventName, 100);

                        printf("\nEnter the number of competitors: \n");
                        scanf("%d", &newEvent->numCompetitors); 

                        printf("\nEnter event gender: \n"); 
                        readline(newEvent->gender, 1); 

                        newEvent->next = curEvent; 

                        if(prevEvent == NULL)
                        {
                            eventDB = newEvent;
                        } 

                        else
                        {
                            prevEvent->next = newEvent; 
                        }

                        break; 
                    }

            // ========== case s, EVENT search for an event ======== // 

                    case 's':

                    {
                        int num; 
                        struct event *newEvent; 
                        // prompt user for the event number 
                        printf("\nEnter the event number: \n"); 
                        scanf("%d", &num);

                        newEvent = findEvent(num);

                        // if the event exists, we print out the event data 
                        if(newEvent != NULL)
                        {
                            printf("\nEvent Code: %d", newEvent->eventCode); 
                            printf("\nEvent Name: %s", newEvent->eventName); 
                            printf("\nNumber of Competitors: %d", newEvent->numCompetitors); 
                            printf("\nEvent Gender: %s", newEvent->gender); 
                        }
                        
                        // if event does not exist, print out a not found message 
                        else
                        {
                            printf("\nThe event was not found.\n"); 
                            
                        }

                        break; 
                        
                    }

                 // ======= case u, EVENT update ======= // 
                    case 'u':
                    {
                        int num, newCode, newComp;
                        struct event *newEvent; 

                        printf("\nEnter the event code: \n"); 
                        scanf("%d", &num); 
                        
                        newEvent = findEvent(num); 
                        if(newEvent != NULL)
                        {
                            printf("\nEnter the *NEW* event CODE: ");
                            scanf("%d", &newCode); 
                            newEvent->eventCode += newCode;

                            printf("\nEnter the *NEW* event NAME: ");
                            readline(newEvent->eventName, 100);

                            printf("\nEnter the *NEW* number of competitors: "); 
                            scanf("%d", &newComp);
                            newEvent->numCompetitors += newComp;

                            printf("\nEnter the *NEW* GENDER: ");
                            readline(newEvent->gender, 1);
                        }
                        
                    }
                    
                // ====== case p, EVENT printing ======= // 

                    case 'p':
                    {
                        struct event *newEvent;
                        printf("Event code      Event Name              Competitors         Gender\n");
                        for(newEvent = eventDB; newEvent != NULL; newEvent = newEvent->next)
                        {
                            printf("%7d          %-25s %11d         %s\n", newEvent->eventCode, newEvent->eventName, newEvent->numCompetitors, newEvent->gender);
                        }
                    } 


                }
            
        }

 // ===========          ATHLETE       ===============    // 
        if (str2 == 'a')
        {
            printf("\nEnter operation code: \n 'i' to input \n 's' to search \n 'u' to update \n 'p' to print \n 'q' to quit\n"); 
                // take in user input 
                scanf("%c", &str1); 
                
                switch(str1)
                {
                    // program will allow user to enter a new event name
                    
                // ======= case i, ATHLETE insert ======== // 
                    case 'i':
                    {       
                        
                        struct athlete *curAthlete, *prevAthlete, *newAthlete; 
                        newAthlete = malloc(sizeof(struct athlete)); 

                        // check if the database is full 
                        if(newAthlete == NULL)
                        {
                            printf("\nThe athlete database is full\n"); 
                            return 0; 
                        }

                        // if not full then do this 
                        printf("\nEnter the Athlete code: \n"); 
                        scanf("%d", &newAthlete->athleteCode); 


                        for(curAthlete = athleteDB, prevAthlete = NULL; curAthlete != NULL && newAthlete->athleteCode > curAthlete->athleteCode; prevAthlete = curAthlete, curAthlete = curAthlete->next); 

                        if(curAthlete != NULL && newAthlete->athleteCode == curAthlete->athleteCode)
                        {
                            printf("\nThe athlete already exists\n");
                            free(newAthlete);
                            return 0; 
                        } 
 

                        printf("\nEnter the Athlete name: \n"); 
                        readline(newAthlete->athleteName, 100);

                        printf("\nEnter Athlete gender: \n"); 
                        readline(newAthlete->athleteGender, 1); 
                        newAthlete->next = curAthlete; 

                        printf("\nEnter Athlete Age: \n"); 
                        scanf("%d", &newAthlete->athleteAge); 


                        if(prevAthlete == NULL)
                        {
                            athleteDB = newAthlete;
                        } 

                        else
                        {
                            prevAthlete->next = newAthlete; 
                        }

                        break; 
                    }

            // ========== case s, ATHLETE search for an event ======== // 

                    case 's':

                    {
                        int num; 
                        struct athlete *newAthlete; 
                        // prompt user for the athlete code 
                        printf("\nEnter the athlete code: \n"); 
                        scanf("%d", &num);

                        newAthlete = findAthlete(num);

                        // if the athlete exists, we print out the event data 
                        if(newAthlete != NULL)
                        {
                            printf("\nAthlete Code: %d", newAthlete->athleteCode); 
                            printf("\nAthlete Name: %s", newAthlete->athleteName); 
                            printf("\nAthlete Gender: %s", newAthlete->athleteGender);
                            printf("\nAthlete Age: %d", newAthlete->athleteAge); 
 
                        }
                        
                        // if athlete does not exist, print out a not found message 
                        else
                        {
                            printf("\nThe Athlete was not found.\n"); 
                            
                        }

                        break; 
                        
                    }

                 // ======= case u, ATHLETE update ======= // 
                    case 'u':
                    {
                        int num, newCode, newComp;
                        struct athlete *newAthlete; 

                        printf("\nEnter the Athlete code: \n"); 
                        scanf("%d", &num); 
                        
                        newAthlete = findAthlete(num); 
                        if(newAthlete != NULL)
                        {
                            printf("\nEnter the *NEW* athlete CODE: ");
                            scanf("%d", &newCode); 
                            newAthlete->athleteCode += newCode;

                            printf("\nEnter the *NEW* athlete NAME: ");
                            readline(newAthlete->athleteName, 100);

                            printf("\nEnter the *NEW* GENDER: ");
                            readline(newAthlete->athleteGender, 1);

                            printf("\nEnter the *NEW* Athlete Age: \n"); 
                            scanf("%d", &newAthlete->athleteAge);
                        }
                        
                    }  

                // ====== case p, ATHLETE printing ======= // 

                    case 'p':
                    {
                        struct athlete *newAthlete;
                        printf("Athlete code      Athlete Name         Age            Gender\n");
                        for(newAthlete = athleteDB; newAthlete != NULL; newAthlete = newAthlete->next)
                        {
                            printf("%7d          %-25s %11d         %s\n", newAthlete->athleteCode, newAthlete->athleteName, newAthlete->athleteAge, newAthlete->athleteGender);
                        }
                    } 


                }

        }

        // if the user selects q to quit, program will quit 

        if (str2 == 'q')
        {
            return 0;
        }

        // otherwise, print out the following message 

        else
        {
            printf("\nPlease select one of the valid options\n");
        }

    }

}





