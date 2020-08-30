 #include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>

#include<gtk/gtk.h> 

#define ARRAYSIZE 100

#define SONGNAME 25

#define SONGARTIST 25

void func1();// Initial Input
void func2();// Show Lib
void func3();// Add a record at the end
void func4();// Edit 
// Search 
// Today's Playlist
void delete_song();//Delete
void func6();//Quit
int tot =0;// Total number of tracks

typedef struct mp3rec// Structure Definition
{

char name[SONGNAME];

char artist[SONGARTIST];

int length;

int  tnum;

}d; 

void func1(GtkWidget* widget, gpointer data)//Initial Input 
{ 
       FILE *f1=fopen("mp3lib.dat","wb");
       printf("\nEnter the number of track records you want to enter:\n"); 
        int n; 
        scanf("%d",&n);
        tot = tot + n;
        printf("\nTotal records in file: %d ",tot);
        struct mp3rec a[n]; 
        printf("\nEnter the details of the track records:\n"); 
        for(int i=0;i<n;++i)
        { 
            printf("\nEntering data for track record %d\n",i+1); 
            printf("\n Enter the name of the song:\n"); 
            scanf("%s", a[i].name); 
            printf("\n Enter the name of the artist:\n");
            scanf("%s", a[i].artist);
            printf("\n Enter the length of the song:\n");
            scanf("%i",&a[i].length); 
            printf("\n Enter the track number:\n");
            scanf("%i",&a[i].tnum); 
            fwrite(&a[i],sizeof(a[i]),1,f1); 
            /*if (fwrite)
                printf("\nAdded Record %d\n",i+1);
            else 
                printf("\nError in writing file\n");*/

        } 
        printf("\n\n Added Records \n\n");
        fclose(f1); 
}  

void func2(GtkWidget* widget, gpointer data)//Displays song library
{ 
    printf("\nDisplaying the entire song library:\n"); 
    FILE* f1=fopen("mp3lib.dat","rb"); 
    fseek(f1, 0, SEEK_SET);//Sets the pointer back to first file
    struct mp3rec a[tot]; 
    int i=0;
    while(i<tot)
    { 
        fread(&a[i],sizeof(a[i]),1,f1);
        printf("\nName of the song:%s\n",a[i].name);
        printf("\nName of the artist:%s\n",a[i].artist);
        printf("\nLength of the song:%d\n",a[i].length);
        printf("\nTrack number:%d\n",a[i].tnum); 
        i++;
    } 
    fclose(f1);
}

void func3(GtkWidget* widget, gpointer data)//Appends record 
{ 
    struct mp3rec a;
    tot+=1;
    FILE *f1=fopen("mp3lib.dat","a+b");
    printf("\nEnter the details of the track record:\n"); 
    for(int i=0;i<1;++i)
    { 
        printf("\n Enter the name of the song:\n"); 
        scanf("%s", a.name); 
        printf("\n Enter the name of the artist:\n");
        scanf("%s", a.artist);
        printf("\n Enter the length of the song:\n");
        scanf("%i", &a.length); 
        printf("\n Enter the track number:\n");
        scanf("%i", &a.tnum); 
        fwrite(&a,sizeof(a),1,f1); 
        /*if (fwrite)
            printf("\nAdded Record %d\n",i+1);
        else 
            printf("\nError in writing file\n");*/

    } 
    printf("\n\n Added Record \n\n");
    fclose(f1); 
}

void func6(GtkWidget* widget, gpointer data)//Today's Playlist
{ 
    struct mp3rec m;
    int nRandonNumber = 0;
    int t=1; 
    int p=0;
    FILE *f1=fopen("mp3lib.dat","rb"); 
    if(!f1)
		printf("\nFile could not be opened\n");
    while(getc(f1)!=EOF)
    {
        fread(&m,sizeof(m),1,f1);
        if(m.tnum)
            p++;
        else
            continue;
    } 
    if(p<3) 
        printf("\nInsufficient track records:"); 
    else  
    {
    fseek(f1, 0, SEEK_SET);
    struct mp3rec a;
    int j=0;
    srand(time(NULL));
    printf("\nHere's a playlist for you today:\n");
    for (int i = 0; i < 3; i++)//3 random songs to make up the playlist
    {
        nRandonNumber = rand()%(tot-0) + 1;//Generating random track no.
        while(j<tot)
        { 
            
            fread(&a,sizeof(a),1,f1);
            if(a.tnum==nRandonNumber)
                {
                    printf("\n\n%d Song Name: %s",t++,a.name);
                    printf("\n Artist: %s\n",a.artist);
                }
            j++;
        } 
        j=0; 
        fseek(f1, 0, SEEK_SET); 
     }//End of for
    }//ENd of else  
    fclose(f1);
} 

void delete_song(GtkWidget* widget, gpointer data)
{
	FILE *fo=fopen("mp3lib.dat","rb");                   //Original file
	FILE *fn=fopen("temp.dat","wb");                     //Temp file
	int found = 0;
	int n,r;
	struct mp3rec a;
	printf("\nEnter track record to be deleted: \n");
	scanf("%d",&n);
	while(fread(&a,sizeof(a),1,fo)!=NULL)
	{
		if(a.tnum==n)
		{
			printf("Track located...deleteing...\n");
			printf("Track deleted successfully\n");
			found = 1;
			tot = tot-1;
		}
		else
			fwrite(&a,sizeof(struct mp3rec),1,fn);
	}
	
	if(!found)
		printf("The record could not be located\n");
	
	fclose(fo);
	fclose(fn);
	remove("mp3lib.dat");                                    //removing the original file
	
	r=rename("temp.dat","mp3lib.dat");                       //renaming the temporary file
	if(r==0)
		printf("Rename successful\n");
	else
		printf("Unsuccessful\n");
	
}

void search_lib(GtkWidget* widget, gpointer data)
{
	int n,found=0;
	struct mp3rec a;
	FILE *f1 = fopen("mp3lib.dat","rb");
	if(!f1)
		printf("\nFile could not be opened\n");
	
	printf("Enter track number you want to search: \n");
	scanf("%d",&n);
	
	while(fread(&a,sizeof(a),1,f1)!=NULL)
	{
		if(a.tnum==n)                                             //condition to search req record
		{
			printf("Record found\nDetails of record: \n");        //Displays details of searched record
			printf("Track number : %d\n",a.tnum);
			printf("\nName : %s",a.name);
			printf("\nArtist : %s",a.artist);
			printf("\nDuration : %d\n",a.length);
			found = 1;
			break;
		}
	}
	if(found == 0)
		printf("\nRecord doesn't exist");
	fclose(f1);
	
}



void modify(GtkWidget* widget, gpointer data)
{
	struct mp3rec a;
	int n;
	int found = 0;
	long size = sizeof(a);
	
	FILE *f1 = fopen("mp3lib.dat","r+b");
	
	printf("Enter the track number you want to modify: \n");
	scanf("%d",&n);
	
	while(fread(&a,sizeof(a),1,f1)!=NULL)
	{
		if(a.tnum==n)
		{
			fseek(f1,-size,SEEK_CUR);                                   //sets file pointer to start of found rec
			for(int i=0;i<1;i++)
			{
				printf("\n Enter the name of the song:\n");             //Takes input to modify record
				scanf("%s", a.name); 
				printf("\n Enter the name of the artist:\n");
				scanf("%s", a.artist);
				printf("\n Enter the length of the song:\n");
				scanf("%i", &a.length); 
				printf("\n Enter the track number:\n");
				scanf("%i", &a.tnum); 
				fwrite(&a,sizeof(a),1,f1); 
			}
			
			printf("Record updated\n");
			found = 1;
			break;
		}
	}
	fclose(f1);
	if(found == 0)
		printf("Track not found\n");
}

void destroy(GtkWidget* widget, gpointer data) // For closing the window 
{ 
    gtk_main_quit(); 
} 
  
int main(int argc, char* argv[]) 
{ 
  
    GtkWidget* window;   
    GtkWidget* button1;
    GtkWidget* button2;    
    GtkWidget* button3;  
    GtkWidget* button4;  
    GtkWidget* button5;  
    GtkWidget* button6;  
    GtkWidget* button7;
    GtkWidget* label; 
    GtkWidget* table; 
    
    gtk_init(&argc, &argv); //Initialisation
  
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL); //Creating a framed window
  
    g_signal_connect(window, "destroy", 
                     G_CALLBACK(destroy), NULL); //function call to close the window
    /* Let's set the border width of the window to 20. 
    * You may play with the value and see the 
    * difference. */
    gtk_container_set_border_width(GTK_CONTAINER(window), 20); //Setting the border of the window
    
    table=gtk_table_new(3,3,0);//Creation of table 

    button1 = gtk_button_new_with_label("Click Me!"); //Text entry for the button
    label=gtk_label_new("Use this to enter details"); //Text entry for the label
    gtk_table_attach(GTK_TABLE(table),label,0,1,0,1,GTK_FILL,GTK_FILL,0,0);//Placing of label
    gtk_table_attach(GTK_TABLE(table),button1,1,2,0,1,GTK_FILL,GTK_FILL,0,0);//Placing of button
    
    button2 = gtk_button_new_with_label("Click Me!"); //Text entry for the button
    label=gtk_label_new("Displays music library"); //Text entry for the label
    gtk_table_attach(GTK_TABLE(table),label,0,1,1,2,GTK_FILL,GTK_FILL,0,0);//Placing of label
    gtk_table_attach(GTK_TABLE(table),button2,1,2,1,2,GTK_FILL,GTK_FILL,0,0);//Placing of button
 
    button3 = gtk_button_new_with_label("Click Me!");//Text entry for the button
    label=gtk_label_new("Appends a given record");//Text entry for the label
    gtk_table_attach(GTK_TABLE(table),label,0,1,2,3,GTK_FILL,GTK_FILL,0,0);//Placing of label
    gtk_table_attach(GTK_TABLE(table),button3,1,2,2,3,GTK_FILL,GTK_FILL,0,0);//Placing of button
       
    button4 = gtk_button_new_with_label("Click Me!"); //Text entry for the button
    label=gtk_label_new("Deletes a record");//Text entry for the label
    gtk_table_attach(GTK_TABLE(table),label,0,1,3,4,GTK_FILL,GTK_FILL,0,0);//Placing of label
    gtk_table_attach(GTK_TABLE(table),button4,1,2,3,4,GTK_FILL,GTK_FILL,0,0);//Placing of button
       
     button5=gtk_button_new_with_label("Click Me!"); //Text entry for the button
    label=gtk_label_new("Searches a given record");//Text entry for the label
    gtk_table_attach(GTK_TABLE(table),label,0,1,4,5,GTK_FILL,GTK_FILL,0,0);//Placing of label
    gtk_table_attach(GTK_TABLE(table),button5,1,2,4,5,GTK_FILL,GTK_FILL,0,0);//Placing of button
       
     button6 = gtk_button_new_with_label("Click Me!"); //Text entry for the button
    label=gtk_label_new("Modifies a given record");//Text entry for the label
    gtk_table_attach(GTK_TABLE(table),label,0,1,5,6,GTK_FILL,GTK_FILL,0,0);//Placing of label
    gtk_table_attach(GTK_TABLE(table),button6,1,2,5,6,GTK_FILL,GTK_FILL,0,0);//Placing of button
       
    button7 = gtk_button_new_with_label("Click Me!"); //Text entry for the button
    label=gtk_label_new("Displays today's viral playlist");//Text entry for the label
    gtk_table_attach(GTK_TABLE(table),label,0,1,6,7,GTK_FILL,GTK_FILL,0,0);//Placing of label
    gtk_table_attach(GTK_TABLE(table),button7,1,2,6,7,GTK_FILL,GTK_FILL,0,0);//Placing of button
    
    g_signal_connect(GTK_OBJECT(button1), 
                     "clicked", G_CALLBACK(func1), 
                     "button"); //function call for button1
    g_signal_connect(GTK_OBJECT(button2), 
                     "clicked", G_CALLBACK(func2), 
                     "button"); //function call for button2
    g_signal_connect(GTK_OBJECT(button3), 
                     "clicked", G_CALLBACK(func3), 
                     "button");//function call for button3
    g_signal_connect(GTK_OBJECT(button4), 
                     "clicked", G_CALLBACK(delete_song), 
                     "button");//function call for button4
    g_signal_connect(GTK_OBJECT(button5), 
                     "clicked", G_CALLBACK(search_lib), 
                     "button");//function call for button5
    g_signal_connect(GTK_OBJECT(button6), 
                     "clicked", G_CALLBACK(modify), 
                     "button");//function call for button6
    g_signal_connect(GTK_OBJECT(button7), 
                     "clicked", G_CALLBACK(func6), 
                     "button");//function call for button7

    gtk_container_add(GTK_CONTAINER(window),table); //Placing of table on the window
  
    gtk_widget_show_all(window); //Displays the window
    
     //Calculating total records first
    FILE* f2=fopen("mp3lib.dat","rb"); 
    struct mp3rec m;
    while(getc(f2)!=EOF)
    { 
        fread(&m,sizeof(m),1,f2); 
        if(m.tnum)
            tot++;
        else 
            continue; 
    } 
    printf("\nTotal records found in the file %i",tot);
    fclose(f2);
 
    
    gtk_main(); 
  
    return 0; 
} 

