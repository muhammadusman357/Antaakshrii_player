#include <iostream>
#include <string>
#include <limits>
#include "player.cpp"
using namespace std;

int space;
void top_title();
int getIntegerInput(const string& prompt);
class Song{
public:
    string title;
    string artist;
    string mood;
    string type;
    Song* next;
    Song* prev;

    
	Song() : next(nullptr), prev(nullptr){}
	Song(string t, string a,string m ,string t2) : title(t), artist(a), mood(m), type(t2) , next(nullptr), prev(nullptr) {}
 
	void details()
	{
		top_title();
    	cout << "|              Song Details              |" << endl;
    	cout << "|----------------------------------------|" << endl;
    	space = 34 - title.size();
    	cout << "| Song: " << title << setfill(' ') << setw(space) << "|" << endl;
    	cout << "|                                        |" << endl;
    	space = 32 - artist.size();
    	cout << "| Artist: " << artist << setfill(' ') << setw(space) << "|" << endl;
    	cout << "|                                        |" << endl;
    	space = 34 - mood.size();
    	cout << "| Mood: " << mood << setfill(' ') << setw(space) << "|" << endl;
    	cout << "|                                        |" << endl;
    	space = 34 - type.size();
    	cout << "| type: " << type << setfill(' ') << setw(space) << "|" << endl;
    	cout << "|----------------------------------------|" << endl;
    	cout << "| Press a key to go Back                 |" << endl;
    	cout << "|________________________________________|";
    	_getch();
	}
};

void top_title()
{
	clearScreen();
    setConsoleTextAttribute(FOREGROUND_GREEN);
    
    cout << "|========================================|";
    cout << endl;
    cout << "|" << setfill(' ') << setw(25) << "Antakshri" << setfill(' ') << setw(16) << "|" << endl;
    cout << "|========================================|";
    cout << endl;
}
class Queue {
private:
    Song* front;
    Song* rear;
    int count = 0;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(Song* song) 
	{
	    char opt;
	    if (front == nullptr) { // queue empty
	        front = rear = new Song(song->title, song->artist,song->mood,song->type);
	        front->next = front->prev = front; // circular reference for a single node
	    } else {
	        if (song->title == rear->title) {
	        	cout << "|----------------------------------------|" << endl;
	            cout << "| You have already added this song.      |" << endl;
				cout << "| Do you want to add it again? (y/n)     |" << endl;
				cout << "|----------------------------------------|" << endl;
				cout << " Choice=> ";
	            cin >> opt;
	            if (opt == 'n') {
	                return;
 	           }
	        }
		        Song* temp = new Song(song->title, song->artist, song->mood, song->type);
	        temp->prev = rear;
	        temp->next = front;
	        rear->next = temp;
	        front->prev = temp;
            rear = temp;
        }
        count++;
    }
	void dequeue() {
        if (front == nullptr) {
            cout << "Queue is empty. Cannot dequeue." << endl;
            return;
        }

        Song* temp = front;

        if (front == rear) {
            // Only one node in the list
            delete front;
            front = rear = nullptr;
        } else {
            front = front->next;
            front->prev = rear;
            rear->next = front;
            delete temp;
        }

        count--;
    }

    Song* getFront() {
        if (front == nullptr) {
            return nullptr;
        }
        return front;
    }
    void clearQueue() {
        if (front == nullptr) {
            cout << "Queue is already empty." << endl;
            return;
        }

        Song* current = front;
        Song* nextNode;

        do {
            nextNode = current->next;
            delete current;
            current = nextNode;
        } while (current != front);

        front = rear = nullptr;
        count = 0;

        cout << "Queue cleared." << endl;
    }
    void displayTitles() {
    	top_title();
    	cout << "|                  Queue                 |" << endl;
		cout << "|----------------------------------------|" << endl;
        
        if (front == nullptr) {
            cout << "|            Queue is empty.             |" << endl;
            cout << "|________________________________________|";
        	cout << endl;
            return;
        }
		
        Song* current = front;
        do{
        	space = 40 - current->title.size();
            cout << "| " << current->title << setfill(' ') << setw(space) << "|" << endl;
            current = current->next;
        }while (current != front);
        cout << "|________________________________________|";
        cout << endl;
    }
    
    int getQueuecount(){
    	return count;
	}
};

Queue Q;

class CircLL{
public:
	int count;
    Song* head;
    Song* tail;
    CircLL() : head(nullptr), tail(nullptr), count(0) {}
	
	
	
	void addatTAIL(string t, string a,string m,string t2) {
    	
        Song* newnode = new Song(t,a,m,t2);
        if (head == nullptr) {
            head = tail = newnode;
            head->next = head->prev = newnode;
            tail->next = tail->prev = newnode;
        } else {
            newnode->prev = tail;
            tail->next = newnode;
            newnode->next = head;
            head->prev = newnode;
            tail = newnode;
            
        }
        count++;
    }
	
    void addatHEAD(string t, string a,string m,string t2) {
    	
        Song* newnode = new Song(t, a,m,t2);
        if (head == nullptr) {
            head = tail = newnode;
        } else {
            newnode->prev = tail;
            tail->next = newnode;
            newnode->next = head;
            head->prev = newnode;
            head = newnode;
            
        }
        count++;
    }

	void delNode(int p) {
    if (head == nullptr) {
        cout << "List is empty. Cannot delete." << endl;
        return;
    }
	int i = 0;
    Song* current = head;
    do {
        if (++i==p) {
            // Found the node to delete
            if (current == head && current == tail) {
                // Only one node in the list
                delete current;
                head = tail = nullptr;
            } else {
                // Update adjacent nodes' pointers
                current->prev->next = current->next;
                current->next->prev = current->prev;

                // Update head and tail if necessary
                if (current == head) {
                    head = current->next;
                } else if (current == tail) {
                    tail = current->prev;
                }

                delete current;
            }
            cout << "|----------------------------------------|" << endl;
        	cout << "|       Node deleted successfully.       |" << endl;
        	cout << "|________________________________________|" << endl;
            count--;
            return;
        }
        current = current->next;
    } while (current != head);
		cout << "|----------------------------------------|" << endl;
        cout << "|       Node not found in the list       |" << endl;
        cout << "|________________________________________|" << endl;
}
	
	void ReadAllSongs(string filename)
	{
    ifstream f2(filename);
    if (f2.is_open())
    {
        string line;
		string title,artist,mood,type;
        while (getline(f2, line))
        {
        	int i = 0;
            istringstream iss(line);
            iss >> i >> title >> artist >> mood >> type;
            //current = current->next;
            addatTAIL(title, artist,mood,type);
    	}
    	f2.close();
    	return;
    }
    else
    {
        cout << "|----------------------------------------|" << endl;
        cout << "|          File Does not Exist.          |" << endl;
        cout << "|________________________________________|" << endl;
        return;
    }
	}
	
	void writeAllSongs(string filename)
    {
    	Song* current = head;
    	//string filename = ""
        ofstream file(filename);
        if (file)
        {
        	int i=1;
        	do{
        		setfill(' ');
        		file << i << setw(25) << current->title << setw(25) << current->artist << setw(25) << current->mood << setw(25) << current->type << endl;
        		current=current->next;
        		i++;
			}while(current != head);
            

            file.close();
            cout << "Data written to file successfully." << endl;
        }
        else
        {
            cout << "Error opening file." << endl;
        }
    }
    string gettitle(CircLL A1)
    {
    	return A1.head->title;
	}
	string getartist(CircLL A1)
	{
		return A1.head->artist;
	}
	void titles()
	{
		Song *current=head;
		int i = 0;
		do{
			space = 38 - current->title.size();
        	cout << "| " << ++i << "." << current->title << setfill(' ') << setw(space) << "|" << endl;
        	current = current->next;
    	}while(current != head);
	}
	
	int get_count(){
		return count;
		
	}


};
string currentuser;
class playlist
{
	public:
	CircLL list;
	string playlistName;
	playlist* link;
	playlist(){
		link = nullptr;
	}
	playlist(string Name){
		playlistName = Name;
		link = nullptr;
	}
	
	
	
};
class PlayListManager{
private:
	playlist* plHead;
	playlist* plTail;
	int plcount;
	
public:
    PlayListManager(){
    	plHead = nullptr;
    	plcount = 0;
	}
	playlist* get_plhead(){return plHead;}
	int get_plcount(){return plcount;}
	
	void Addplaylist(string name,CircLL &songList)
	{
    	playlist* newnode = new playlist(name);
    	newnode->list = songList;
    	if (plHead == NULL) 
		{
        	plHead = newnode;
        	newnode->link = newnode;
        	plTail = newnode; 
    	} 
		else 
		{
        	playlist* temp = plHead;
        	while (temp->link != plHead) 
			{
            	temp = temp->link;
        	}
        	temp->link = newnode;
        	newnode->link = plHead;
        	plTail = newnode; 
    	}
    plcount++;
	}
	
	void clear() {
		int i = get_plcount();
        while (plHead!=nullptr && i>0) {
        	deletePlaylistNode(i);
        	i--;
        }
    }
	
	
	void writeAllPlaylistsToFile()
    {
    	string userplaylistfile = currentuser + "-" + "All-Playlists.txt";
    ofstream file(userplaylistfile);
    if (file.is_open())
    {
        playlist* temp = plHead;
		if(plHead==nullptr)
		{
			const char* user1 = userplaylistfile.c_str();
			file.close();
			remove(user1);
			
		}
		else{
        do
        {
            file << "PlaylistName: " << temp->playlistName << endl;

            Song* current = temp->list.head;
            int i = 1;
            do
            {
                file << i << setw(25) << current->title << setw(25) << current->artist << setw(25) << current->mood << setw(25) << current->type << endl;
                current = current->next;
                i++;
            } while (current != temp->list.head);

            file << "EndPlaylist" << endl;
            temp = temp->link;
        }while (temp != plHead);
        file.close();
        cout << "Data written to file successfully." << endl;
		}
        
    }
    else
    {
        cout << "Error opening file." << endl;
    }
}

    void readAllPlaylistsFromFile()
	{
	string userplaylistfile = currentuser + "-" + "All-Playlists.txt";
    ifstream file(userplaylistfile);
    if (file.is_open())
    {
    	clear();
        playlist* currentPlaylist = nullptr;
        string line;

        while (getline(file, line))
        {
            if (line.find("PlaylistName:") != string::npos)
            {
                // Found a new playlist
                if (currentPlaylist != nullptr)
                {
                    // Add the previous playlist to the PlayListManager
                    Addplaylist(currentPlaylist->playlistName, currentPlaylist->list);
                    delete currentPlaylist;
                }

                // Extract the playlist name
                size_t colonPos = line.find(':');
                if (colonPos != string::npos)
                {
                    currentPlaylist = new playlist(line.substr(colonPos + 2));
                }
            }
            else if (line.find("EndPlaylist") != string::npos)
            {
                // End of playlist
                if (currentPlaylist != nullptr)
                {
                    // Add the current playlist to the PlayListManager
                    Addplaylist(currentPlaylist->playlistName, currentPlaylist->list);
                    delete currentPlaylist;
                    currentPlaylist = nullptr;
                }
            }
            else
            {
                // Read song data
                string title, artist, mood, type;
                int i;
                istringstream iss(line);
                iss >> i >> title >> artist >> mood >> type;
                if (currentPlaylist != nullptr)
                {
                    // Add song to the current playlist
                    currentPlaylist->list.addatTAIL(title, artist, mood, type);
                }
            }
        }

        // Check if there's an incomplete playlist at the end of the file
        if (currentPlaylist != nullptr)
        {
            Addplaylist(currentPlaylist->playlistName, currentPlaylist->list);
            delete currentPlaylist;
        }

        file.close();
    }
    else
    {
        cout << "|----------------------------------------|" << endl;
        cout << "|          File Does not Exist.          |" << endl;
        cout << "|________________________________________|" << endl;
        return;
    }
}

	
	
    void deletePlaylistNode(int pos) {
    if (plHead == nullptr) {
    	cout << "|----------------------------------------|" << endl;
        cout << "|              No Playlist.              |" << endl;
        cout << "|________________________________________|" << endl;
        return;
    }

    playlist* temp = plHead;
    playlist* prev = nullptr;
	
	
    for (int i = 1; i < pos; ++i) {
        prev = temp;
        temp = temp->link;
    }

    if (temp == plHead) {
        if (temp->link == plHead) {
            // Only one playlist, update plHead and plTail
            plHead = plTail = nullptr;
        } else {
            // More than one playlist, update plHead and plTail
            plHead = plHead->link;
            plTail->link = plHead;
        }
    } else {
        prev->link = temp->link;

        if (temp == plTail) {
            // If the playlist being deleted is the tail, update plTail
            plTail = prev;
        }
    }

    delete temp;
    plcount--;
}


	
	
	
    void ShowPlaylist(){
 	playlist* temp=plHead;
 	int i=1;
    do
    {
        cout<< i+1 << ". " << temp->playlistName << endl;
        i++;
        temp=temp->link;
    } while (temp!=plHead);
    cout<<endl;
 }
};

    bool Rabincrap(string pattern, string text) 
	{
        int M = pattern.size();
        int N = text.size();
        if (N < M) 
		{
            return false; 
        }
        int d = 256;
        long long int p = 0; 
        long long int t = 0; 
        long long int h = 1;
        for (int i = 0; i < M - 1; i++) 
		{
            h = (h * d);
        }
        for (int i = 0; i < M; i++) 
		{
            p = (d * p + pattern[i]);
            t = (d * t + text[i]);
        }
        for (int i = 0; i <= N - M; i++)
		 {
            if (p == t) {
                bool found = true;
                for (int j = 0; j < M; j++) 
				{
                    if (text[i + j] != pattern[j]) 
					{
                        found = false;
                        break;
                    }
                }
                if (found) 
				{
                    return true;
                }
            }
            if (i < N - M) 
			{
                t = (d * (t - text[i] * h) + text[i + M]);
            }
        }
        return false; 
    }
    void Options1(Song* selected);
	void searcher(CircLL &songList,int temp)
	{
    Song* current = songList.head;
    Song* matches[100];
    int matchCount = 0;
    int choice = 0;
    string pattern;
    int m2 = 1;
    
    top_title();
    //cout << "|========================================|" << endl;
    cout << "|                 Search                 |" << endl;
    cout << "|----------------------------------------|" << endl;
    string te;
    	if(temp==1)
    		te = "|                Song Name               |";
    	else if(temp==2)
    		te = "|                 Artist                 |";
    	else if(temp==3)
    		te = "|                  Mood                  |";
    	else if(temp==4)
    		te = "|                  Type                  |";
    cout << te << endl;
    cout << "|________________________________________|"<< endl;
    cout << " Search : ";
    
    cin >> pattern;
    cout << "|========================================|" << endl;
    for (int i = 0; i < songList.get_count(); i++) {
        string target;
        if (temp == 1) {
        	
            target = current->title;
        } else if (temp==2) {
            target = current->artist;
		} else if (temp==3) {
            target = current->mood;

        } else if (temp==4) {
            target = current->type;
        }
        if (Rabincrap(pattern, target)) {
            if (matchCount < 100) {
                matches[matchCount++] = current;
            } else {
                cout << "|      Maximum match limit reached.      |" << endl;
                cout << "|________________________________________|"<< endl;
                break;
            }
        }
        current = current->next;
    }
    if (matchCount == 0) {
    	cout << "|               Not found.               |" << endl;
        cout << "|________________________________________|"<< endl;
    } else {
    	//m2 = matchCount;
    	do{
    	top_title();
    	//cout << "|========================================|" << endl;
    	cout << "|                 Search                 |" << endl;
    	cout << "|----------------------------------------|" << endl;
    	//string te;
    	cout << te << endl;
    	space = 33 - pattern.size();
    	cout << "|----------------------------------------|" << endl;
    	cout << "| Query: " << pattern << setfill(' ') << setw(space) << "|" << endl;
    	cout << "|----------------------------------------|" << endl;
        //cout << "Multiple matches found:" << endl;
        for (int i = 0; i < matchCount; i++) {
        	space = 37 - matches[i]->title.size();
            cout << "| " << i + 1 << ". " << matches[i]->title << setfill(' ') << setw(space) << "|" << endl;
        }
        cout << "| 0. Back                                |" << endl;
        cout << "|________________________________________|"<< endl;
        
        
        	cout << "Choice=> ";
        	cin >> choice;
        	while (choice < 0 || choice > matchCount) {
        	//cout << "|----------------------------------------|" << endl;
            cout << "| Invalid choice! Please select a number between 1 and " << matchCount << endl;
			cout << "Choice=> ";
            cin >> choice; 
        	}
			if(choice>0)	
        		Options1(matches[choice - 1]);
        	//m2--;
    
		}while(choice!=0);}
        //int a;
        //a = _getch();
    }


void Options1(Song* selected);
PlayListManager PLM;

void insertionSort(CircLL& playlist) {
    if (!playlist.head || playlist.head->next == playlist.head) return;
    CircLL sortedList;
    while (playlist.head != playlist.tail) {
        Song* current = playlist.head;
        playlist.head = playlist.head->next;
        playlist.head->prev = playlist.tail;
        playlist.tail->next = playlist.head;
        Song* iter = sortedList.head;
        if (!iter || iter->title >= current->title) { 
            if (sortedList.head) {
                current->next = sortedList.head;
                current->prev = sortedList.tail;
                sortedList.head->prev = current;
                sortedList.tail->next = current;
                sortedList.head = current;
            } else { 
                sortedList.head = sortedList.tail = current;
                current->next = current->prev = current;
            }
        } else {
            while (iter->next != sortedList.head && iter->next->title < current->title) {
                iter = iter->next; 
            }
            current->next = iter->next;
            current->prev = iter;
            iter->next->prev = current;
            iter->next = current;
            if (iter == sortedList.tail) {
                sortedList.tail = current;
            }
        }
    }
    Song* last = playlist.tail;
    if (!sortedList.head || sortedList.head->title >= last->title) { 
        if (sortedList.head) {
            last->next = sortedList.head;
            last->prev = sortedList.tail;
            sortedList.head->prev = last;
            sortedList.tail->next = last;
            sortedList.head = last;
        } else { 
            sortedList.head = sortedList.tail = last;
            last->next = last->prev = last;
        }
    } else {
        Song* iter = sortedList.head;
        while (iter->next != sortedList.head && iter->next->title < last->title) {
            iter = iter->next; 
        }
        last->next = iter->next;
        last->prev = iter;
        iter->next->prev = last;
        iter->next = last;
        if (iter == sortedList.tail) { 
            sortedList.tail = last;
        }
    }
    playlist.head = sortedList.head;
    playlist.tail = sortedList.tail;
}

int timer_val=0;
//int playlistCount = 1;
 // Assuming a maximum of 10 playlists

class Stack {
private:
    Song* top;
    int stack_size;
	
	void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
	
public:
    Stack() : top(nullptr), stack_size(0) {}

    void push(Song* song) {
        Song* current = new Song(song->title, song->artist,song->mood, song->type);

        if (top == nullptr) {
            current->next = current;
        } else {
            current->next = top;
            Song* temp = top;
            while (temp->next != top) {
                temp = temp->next;
            }
            temp->next = current;
        }

        top = current;
        stack_size++;
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    Song* pop() {
        if (top == nullptr) {
            return nullptr;
        }

        Song* songToPop = top;

        if (top->next == top) {
            // Only one node in the list
            top = nullptr;
        } else {
            Song* temp = top;
            while (temp->next != top) {
                temp = temp->next;
            }
            temp->next = top->next;
            top = top->next;
        }

        songToPop->next = nullptr;
        stack_size--;
		
        return songToPop;
    }

    Song* peek() {
        if (top == nullptr) {
            return nullptr; // or some default value
        }
        return top;
    }

    void displayTimeline()
{
	
	string sl[4];
	sl[0] = "[Play] : Last Played";
    sl[1] = "[Clear Last Played]";
    sl[2] = "[Clear History]";
    sl[3] = "[Back]";

	int size1 = sizeof(sl)/sizeof(sl[0]);
    int selectedOption = 0;
	const int numOptions = size1;
	string temp;
    //sl.artist[]
	//system("COLOR 0e");
	clearScreen();
    while (true) {
    	
        //clearScreen();
		//setConsoleTextAttribute(FOREGROUND_GREEN);
		
        top_title();
        cout << "|                 History                |" << endl;
		if(top==nullptr)
		{
			cout << "|----------------------------------------|" << endl;
			cout << "|             No Song played.            |" << endl;
			cout << "|________________________________________|"<< endl;
			cout << "|----------------------------------------|" << endl;
			cout << "|            History Options.            |" << endl;
    		cout << "|----------------------------------------|" << endl;
			cout << "| ";
			space = 40 - sl[3].size();
			setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
            cout << sl[3];
            setConsoleTextAttribute(FOREGROUND_GREEN);
            cout << setfill(' ') << setw(space) << "|" << endl;
    		cout << "|________________________________________|"<< endl;
    		int key = _getch();
    		if (key == 13)// Enter key
			{
				return;
			}
		}
		else
		{
		cout << "|----------------------------------------|" << endl;
		Song* current = top;
        do {
        	space = 40 - current->title.size();
			cout << "| " << current->title << setfill(' ') << setw(space) << "|" << endl;
            current = current->next;
        } while (current != top);
		cout << "|________________________________________|"<< endl;
		cout << "|----------------------------------------|" << endl;
		cout << "|            History Options.            |" << endl;
    	cout << "|----------------------------------------|" << endl;
        for (int i = 0; i < numOptions; ++i) {
            //setCursorPosition(0, numOptions + i);
            space = 40 - sl[i].size();//total 40 spaces
            if (i == selectedOption) {
                cout << "| ";
				//system("COLOR A4");
                setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
                cout << sl[i];
                //system("COLOR 0A");
                setConsoleTextAttribute(FOREGROUND_GREEN);
                cout << setfill(' ') << setw(space) << "|" << endl;
            }
            else {
                cout << "| ";
                cout << sl[i];
                cout << setfill(' ') << setw(space) << "|" << endl;
            }
            //current = current->next;
        }
        cout << "|________________________________________|";
        cout << endl;

        int key = _getch();

        if (key == 224) {
            key = _getch();
            switch (key) {
            case 72: // Up arrow
            	if (selectedOption > 0) {
                    selectedOption--;
                }
                else
                {
                    selectedOption = numOptions - 1;
				}
                break;
            case 80: // Down arrow
                if (selectedOption < numOptions - 1) {
                    selectedOption++;
                }
                else
                {
                    selectedOption = 0;
				}
                break;
            }
        }
        else if (key == 13)// Enter key
		{ 
            switch(selectedOption)
			{
				case 0:
				{
					Song* selected = peek();
					Options1(selected);
					break;	
				}
				case 1:
					{
					Song* selected = pop();
					delete selected;
					break;
					}
				case 2:
					clear();
					break;
				case 3:
					return;
					break;
			}	
        }
    }
    }
}
	void saveHistoryToFile() {
		string filename = currentuser + "-" + "history.txt";
        ofstream file(filename);
        if (top == nullptr) 
		{
			return;
        }
		Song* current = top;
        if (file.is_open()) {
			
            do {
				setfill(' ');
                file << current->title << setw(25) << current->artist << setw(25) << current->mood << setw(25) << current->type << endl;
            	current = current->next;
        	}while (current != top);
            
			
            file.close();
            cout << "History saved to file successfully." << endl;
        }
        else {
            cout << "Error opening file." << endl;
        }
    }

    // Function to load history from a file
    void loadHistoryFromFile() {
    	string filename = currentuser + "-" + "history.txt";
        ifstream file(filename);

        if (file.is_open()) {
            clear();  // Clear existing history
			Stack* stack1 = new Stack;
			Song* song;
            string line;
            while (getline(file, line)) {
                istringstream iss(line);
                string title, artist, mood, type;
                iss >> title >> artist >> mood >> type;

                song = new Song(title, artist, mood, type);
                stack1->push(song);
            }
            while (stack1->peek()!=nullptr) {
            	song = stack1->pop();
            	push(song);
            }
            delete song;
            delete stack1;
            file.close();
            cout << "History loaded from file successfully." << endl;
        }
        else {
            cout << "Error opening file." << endl;
        }
    }

	
    int getstack_size() const {
        return stack_size;
    }

    Song* mostPlayedSong() {
        if (isEmpty()) {
            cout << "Stack is empty. No songs to find." << endl;
            return nullptr;
        }

        Song* mostFrequent = nullptr;
        Song* current = top;
        int maxCount = 0;

        do {
            int count = 0;
            Song* runner = top;

            do {
                if (current->title == runner->title) {
                    count++;
                }
                runner = runner->next;

            } while (runner != top);

            // Update mostFrequent if necessary
            if (count > maxCount) {
                maxCount = count;
                mostFrequent = new Song(current->title, current->artist,current->mood, current->type);
            }

            current = current->next;
        } while (current != top);

        return mostFrequent;
    }
};
Song* getRandomSong(CircLL& A1)
{
	srand(static_cast<unsigned int>(time(0)));
	if (A1.head == NULL)
		return NULL; 
	int randomIndex = rand() % A1.get_count();
	Song *current = A1.head;
	for (int i = 0; i < randomIndex; ++i)
		current = current->next;
	return current;
}

class UserInfo
{
private:
    int ID;
    string name;
    string username;
    string password;
    string Fav_Gen; // Additional attribute related to the music player
	static int count;
public:
    UserInfo()
    {
    	ID = 0;
        name = "";
        username = "";
        password = "";
        Fav_Gen = "";
    }

    UserInfo(const string &n, const string &un, const string &pw, const string &playerInfo)
        :name(n), username(un), password(pw), Fav_Gen(playerInfo)
    {
    	ID++;
    }

    // Getter and Setter functions
    int getID() const { return ID; }
    string getName() const { return name; }
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getMusicPlayerInfo() const { return Fav_Gen; }

    void setName(const string &n) { name = n; }
    void setUsername(const string &un) { username = un; }
    void setPassword(const string &pw) { password = pw; }
    void setMusicPlayerInfo(const string &info) { Fav_Gen = info; }

    // Encrypt and Decrypt functions
    string encrypt(const string &plaintext, int shift)
    {
        string ciphertext = "";

        for (char ch : plaintext)
        {
            if (isalpha(ch))
            {
                char base = isupper(ch) ? 'A' : 'a';
                ciphertext += (char)((ch - base + shift) % 26 + base);
            }
            else
            {
                ciphertext += ch;
            }
        }

        return ciphertext;
    }

    string decrypt(const string &ciphertext, int shift)
    {
        return encrypt(ciphertext, 26 - shift);
    }

    void writeUserInfo(const string &filename)
    {
        ofstream file(filename, ios::app);
        if (file)
        {
            // Encrypt sensitive information before writing to file
            string encryptedUsername = encrypt(username,10);
            string encryptedPassword = encrypt(password,10);

            file << ID << setw(15) << name << setw(15) << encryptedUsername << setw(15) << encryptedPassword << setw(15) << Fav_Gen;

            /*// Writing playlists to file
            for (const string &playlist : playlists)
            {
                file << setw(10) << playlist;
            }*/

            file << endl;

            file.close();
            cout << "Data written to file successfully." << endl;
        }
        else
        {
            cout << "Error opening file." << endl;
        }
    }
	string Hide_pass()
	{
    START:
    char pass[32];//to store password.
    int i = 0;
    char a;//a Temp char
    for(i=0;;)//infinite loop
    {
        a=_getch();//stores char typed in a
        if((a>='a'&&a<='z')||(a>='A'&&a<='Z')||(a>='0'&&a<='9'))
            //check if a is numeric or alphabet
        {
            pass[i]=a;//stores a in pass
            ++i;
            cout<<"*";
        }
        if(a=='\b'&&i>=1)//if user typed backspace
            //i should be greater than 1.
        {
            cout<<"\b \b";//rub the character behind the cursor.
            --i;
        }
        if(a=='\r')//if enter is pressed
        {
            pass[i]='\0';//null means end of string.
            break;//break the loop
        }
    }
    //cout<<"\nYou entered : "<<pass;
    //here we can even check for minimum digits needed
    if(i<=5)
    {
        cout<<"\n       Minimum 6 digits needed.\n       Enter Again: ";
        _getch();//It was not pausing :p
        goto START;
    }
    string password;
    password = pass;
    return password;
	}
	void displayAll()
    {
        cout << "User ID: " << ID << endl;
        cout << "Name: " << name << endl;
        cout << "Username: " << username << endl;
		cout << "Password: " << password << endl;
		cout << "Genre: " << Fav_Gen << endl;
        /*cout << "Playlists:" << endl;
        for (const string &playlist : playlists)
        {
            cout << " - " << playlist << endl;
        }*/
    }
    bool signIn(const string &filename)
{
    top_title();
    cout << "|                 Login                  |" << endl;
    cout << "|________________________________________|"<< endl;

    int c = 0;
start1:
    cout << endl << "       Username: ";
    string inputUsername;
    string inputPassword;
    cin >> inputUsername;

    cout << endl << "       Password: ";
    inputPassword = Hide_pass();
    //cout << "\n       Show Password(1.Yes, 2.No):\n       => ";
    int pk;
    pk = getIntegerInput("\n       Show Password(1.Yes, 2.No):\n       => ");;
    if (pk == 1)
        cout << "       Password: " << inputPassword << endl << endl ;

    ifstream f2(filename);
    if (f2.is_open())
    {
        string line;
        int fileID;
        string fileUsername, filePassword, filePlayerInfo;
        int flag = 0;

        while (getline(f2, line))
        {
            istringstream iss(line);
            iss >> fileID >> name >> fileUsername >> filePassword >> filePlayerInfo;
            // Decrypt stored username and password for comparison
            string decryptedUsername = decrypt(fileUsername, 10);
            string decryptedPassword = decrypt(filePassword, 10);

            /*cout << "User: " << decryptedUsername << endl;
            cout << "Pass: " << decryptedPassword << endl;
            _getch();*/

            // Comparing input username and password with decrypted values
            if (decryptedUsername == inputUsername && decryptedPassword == inputPassword)
            {
                int space = 32 - inputUsername.size();
                cout << "|----------------------------------------|" << endl;
                cout << "| Login Successful!                      |" << endl;
                cout << "| Welcome " << inputUsername << setfill(' ') << setw(space) << "|" << endl;
                cout << "|________________________________________|\n";
                currentuser = inputUsername;
                int a = _getch();
                f2.close();
                return true;
            }
        }

        if (flag == 0)
        {
            cout << "|----------------------------------------|" << endl;
            cout << "|Invalid Username or password. Try again.|" << endl;
            cout << "|________________________________________|" << endl;
            c++;
        }

        f2.close();

        if (c < 3)
            goto start1;
        else
            return false;
    }
    else
    {
        cout << "|----------------------------------------|" << endl;
        cout << "|          File Does not Exist.          |" << endl;
        cout << "|________________________________________|" << endl;
        return false;
    }
}

};

Stack songStack;
void play_queue()
{
	
	string sl[3];
	sl[0] = "";
    sl[1] = "[Clear Queue]";
    sl[2] = "[Back]";

	int size1 = sizeof(sl)/sizeof(sl[0]);
    int selectedOption = 0;
	const int numOptions = size1;
	string temp;
    //sl.artist[]
	//system("COLOR 0e");
	clearScreen();
    while (true) {
    	
        //clearScreen();
		//setConsoleTextAttribute(FOREGROUND_GREEN);
        Q.displayTitles();
		
		Song* temp = Q.getFront();
		if(temp==nullptr)
		{
			space = 40 - sl[2].size();
			cout << "|----------------------------------------|" << endl;
			cout << "| ";
			setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
            cout << sl[2];
            setConsoleTextAttribute(FOREGROUND_GREEN);
            cout << setfill(' ') << setw(space) << "|" << endl;
    		cout << "|________________________________________|"<< endl;
    		int key = _getch();
    		if (key == 13)// Enter key
			{
				return;
			}
		}
		else
		{

		sl[0] = "[Play] Next: " + temp->title;
		cout << "|----------------------------------------|" << endl;
        for (int i = 0; i < numOptions; ++i) {
            //setCursorPosition(0, numOptions + i);
            space = 40 - sl[i].size();//total 40 spaces
            if (i == selectedOption) {
                cout << "| ";
				//system("COLOR A4");
                setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
                cout << sl[i];
                //system("COLOR 0A");
                setConsoleTextAttribute(FOREGROUND_GREEN);
                cout << setfill(' ') << setw(space) << "|" << endl;
            }
            else {
                cout << "| ";
                cout << sl[i];
                cout << setfill(' ') << setw(space) << "|" << endl;
            }
            //current = current->next;
        }
        cout << "|________________________________________|";
        cout << endl;

        int key = _getch();

        if (key == 224) {
            key = _getch();
            switch (key) {
            case 72: // Up arrow
            	if (selectedOption > 0) {
                    selectedOption--;
                }
                else
                {
                    selectedOption = numOptions - 1;
				}
                break;
            case 80: // Down arrow
                if (selectedOption < numOptions - 1) {
                    selectedOption++;
                }
                else
                {
                    selectedOption = 0;
				}
                break;
            }
        }
        else if (key == 13)// Enter key
		{ 
            switch(selectedOption)
			{
				case 0:
					timer(temp->title,temp->artist);
					songStack.push(temp);
					//songStack.peek();
					Q.dequeue();
    				break;
    			case 1:
    				Q.clearQueue();
    				break;
				case 2:
					return;
    				break;
			}	
        }
    }
    }
}
void song_menu(CircLL& circLL);

void delete_songs(CircLL& circLL,string name2)
{
    int selectedOption = 0;
    int numOptions = circLL.get_count(); // Use the count from CircLL
    clearScreen();
    
    Song* current = circLL.head;
     Song* selected = current;
    
    while (true) {
    	
        top_title();
    	cout << "|              Delete a Song             |" << endl;
    	cout << "|----------------------------------------|" << endl;
   		space = 41 - 16 - name2.size();
    	cout << "| Playlist Name: " << name2 << setfill(' ') << setw(space)<< "|" << endl;
    	cout << "|----------------------------------------|" << endl;
        // Display menu options with highlighted selection
        space = 40 - 9;
        for (int i = 0; i < numOptions; ++i) {
        	//int maxY = getConsoleHeight() - 1;
            //setCursorPosition(0, min(numOptions + i, maxY));
        	
            space = 39 - current->title.size(); 
			
            if (i == selectedOption) {
                cout << "| ";
                setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
                cout  << current->title << " ";
                setConsoleTextAttribute(FOREGROUND_GREEN);
                selected = current;
                cout << setfill(' ') << setw(space) << "|" << endl;
            } else {
                cout << "| ";
                cout  << current->title << " ";
                cout << setfill(' ') << setw(space) << "|" << endl;
            }
            current = current->next;
        }
        
        // Display Exit option after the last song
        //setCursorPosition(0, numOptions + numOptions);
        space = 40 - 6; // Total 40 spaces for "Exit"
        if (selectedOption == numOptions) {
            cout << "| ";
            setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
            cout << "[Back]";
            setConsoleTextAttribute(FOREGROUND_GREEN);
            cout << setfill(' ') << setw(space) << "|" << endl;
        } else {
            cout << "| ";
            cout << "[Back]";
            cout << setfill(' ') << setw(space) << "|" << endl;
        }
        	cout << "|________________________________________|" << endl;
		
        int key = _getch();

        if (key == 224) {
            key = _getch();
            switch (key) {
                case 72: // Up arrow
                    if (selectedOption > 0) {
                        selectedOption--;
                    } else {
                        selectedOption = numOptions;
                    }
                    break;
                case 80: // Down arrow
                    if (selectedOption < numOptions) {
                        selectedOption++;
                    } else {
                        selectedOption = 0;
                    }
                    break;
            }
        } else if (key == 13) { // Enter key
            if (selectedOption == numOptions) {
                return; // Exit program
			} else {
				circLL.delNode(selectedOption+1);
				numOptions = circLL.get_count();
                current = circLL.head;
                selected = current;
            }
        }
    }
}

int getIntegerInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input. Please enter a valid integer." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    return value;
}

void Add_new_songs(CircLL& circLL,playlist* playList)
{
    int selectedOption = 0;
    int numOptions = circLL.get_count(); // Use the count from CircLL
    clearScreen();
    Song* current = circLL.head;
    Song* selected = current;
    
    while (true) {
        top_title();
    	cout << "|             Add a New Song             |" << endl;
    	cout << "|----------------------------------------|" << endl;
   		space = 41 - 16 - playList->playlistName.size();
    	cout << "| Playlist Name: " << playList->playlistName << setfill(' ') << setw(space)<< "|" << endl;
    	cout << "|----------------------------------------|" << endl;
        // Display menu options with highlighted selection
        space = 40 - 9;
        for (int i = 0; i < numOptions; ++i) {
        	//int maxY = getConsoleHeight() - 1;
            //setCursorPosition(0, min(numOptions + i, maxY));
        	
            space = 39 - current->title.size(); 
			
            if (i == selectedOption) {
                cout << "| ";
                setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
                cout  << current->title << " ";
                setConsoleTextAttribute(FOREGROUND_GREEN);
                selected = current;
                cout << setfill(' ') << setw(space) << "|" << endl;
            } else {
                cout << "| ";
                cout  << current->title << " ";
                cout << setfill(' ') << setw(space) << "|" << endl;
            }
            current = current->next;
        }
        
        // Display Exit option after the last song
        //setCursorPosition(0, numOptions + numOptions);
        space = 40 - 6; // Total 40 spaces for "Exit"
        if (selectedOption == numOptions) {
            cout << "| ";
            setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
            cout << "[Back]";
            setConsoleTextAttribute(FOREGROUND_GREEN);
            cout << setfill(' ') << setw(space) << "|" << endl;
        } else {
            cout << "| ";
            cout << "[Back]";
            cout << setfill(' ') << setw(space) << "|" << endl;
        }
        	cout << "|----------------------------------------|" << endl;
        	cout << "| Playlist Songs:                        |" << endl;
        	cout << "|----------------------------------------|" << endl;
        	Song* current2 = playList->list.head;
        	if(current2 != nullptr)
        	{
        	
			do {
        	space = 40 - current2->title.size();
			cout << "| " << current2->title << setfill(' ') << setw(space) << "|" << endl;
            current2 = current2->next;
        	} while (current2 != playList->list.head);
    		}
        	cout << "|________________________________________|" << endl;
		
        int key = _getch();

        if (key == 224) {
            key = _getch();
            switch (key) {
                case 72: // Up arrow
                    if (selectedOption > 0) {
                        selectedOption--;
                    } else {
                        selectedOption = numOptions;
                    }
                    break;
                case 80: // Down arrow
                    if (selectedOption < numOptions) {
                        selectedOption++;
                    } else {
                        selectedOption = 0;
                    }
                    break;
            }
        } else if (key == 13) { // Enter key
            if (selectedOption == numOptions) {
                return; // Exit program
			} else {
				playList->list.addatTAIL(selected->title, selected->artist,selected->mood,selected->type);  
            }
        }
    }
}
void update_playlist(playlist* selected,CircLL &songList)
{
	string sl[4];
    sl[0] = "[View Songs]";
    sl[1] = "[Add Songs]";
    sl[2] = "[Delete Songs]";
    sl[3] = "[Back]";
		int size1 = sizeof(sl)/sizeof(sl[0]);
    	int selectedOption = 0;
		const int numOptions = size1;
		clearScreen();
    	while (true) {
        top_title();
        cout << "|            Playlist Options            |" << endl;
        cout << "|----------------------------------------|" << endl;
        for (int i = 0; i < numOptions; ++i) {
            space = 40 - sl[i].size();//total 40 spaces
            if (i == selectedOption)
			{
                cout << "| ";
				//system("COLOR A4");
                setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
                cout << sl[i] ;
                //system("COLOR 0A");
                setConsoleTextAttribute(FOREGROUND_GREEN);
                cout << setfill(' ') << setw(space) << "|" << endl;
            }
            else {
                cout << "| ";
                cout << sl[i];
                cout << setfill(' ') << setw(space) << "|" << endl;
            }
            //current = current->next;
        }
        cout << "|________________________________________|";
        cout << endl;

        int key = _getch();

        if (key == 224) {
            key = _getch();
            switch (key) {
            case 72: // Up arrow
            	if (selectedOption > 0) {
                    selectedOption--;
                }
                else
                {
                    selectedOption = numOptions - 1;
				}
                break;
            case 80: // Down arrow
                if (selectedOption < numOptions - 1) {
                    selectedOption++;
                }
                else
                {
                    selectedOption = 0;
				}
                break;
            }
        }
        else if (key == 13) { // Enter key
            if (selectedOption == numOptions - 1) {
                return; // Exit
            } else {
                clearScreen();
                if(selectedOption == numOptions - 1)
                	return;
                else
                {
                	switch(selectedOption)
					{
						case 0:
							song_menu(selected->list);
							break;
						case 1:
                        	 Add_new_songs(songList,selected);
							break;
						case 2:
							delete_songs(selected->list,selected->playlistName);
							break;
						case 3:
							return;
							break;
						
					}	
				}
            }
        }
}
}

void Add_new_play(CircLL& circLL) {
    int selectedOption = 0;
    int numOptions = circLL.get_count(); // Use the count from CircLL
    clearScreen();
    Song* current = circLL.head;
    Song* selected = current;
	top_title();
    //cout << "|========================================|" << endl;
    cout << "|           Create New Playlist          |" << endl;
    cout << "|________________________________________|" << endl;
    cout << endl << "     Enter Playlist Name: ";
    string playlistName;
    cin >> playlistName;
    CircLL temp;
    
    while (true) {
        top_title();
        
    	//cout << "|========================================|" << endl;
    	cout << "|           Create New Playlist          |" << endl;
    	cout << "|________________________________________|" << endl;
    	space = 41 - 16 - playlistName.size();
    	cout << "| Playlist Name: " << playlistName << setfill(' ') << setw(space)<< "|" << endl;
		cout << "|========================================|" << endl;
        // Display menu options with highlighted selection
        space = 40 - 9;
        for (int i = 0; i < numOptions; ++i) {
        	//int maxY = getConsoleHeight() - 1;
            //setCursorPosition(0, min(numOptions + i, maxY));
        	
            space = 39 - current->title.size(); 
			
            if (i == selectedOption) {
                cout << "| ";
                setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
                cout  << current->title << " ";
                setConsoleTextAttribute(FOREGROUND_GREEN);
                selected = current;
                cout << setfill(' ') << setw(space) << "|" << endl;
            } else {
                cout << "| ";
                cout  << current->title << " ";
                cout << setfill(' ') << setw(space) << "|" << endl;
            }
            current = current->next;
        }
        
        // Display Exit option after the last song
        //setCursorPosition(0, numOptions + numOptions);
        space = 40 - 6; // Total 40 spaces for "Exit"
        if (selectedOption == numOptions) {
            cout << "| ";
            setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
            cout << "[Back]";
            setConsoleTextAttribute(FOREGROUND_GREEN);
            cout << setfill(' ') << setw(space) << "|" << endl;
        } else {
            cout << "| ";
            cout << "[Back]";
            cout << setfill(' ') << setw(space) << "|" << endl;
        }
		//cout << "|========================================|" << endl;
        	cout << "|----------------------------------------|" << endl;
        	cout << "| Added Songs:                           |" << endl;
        	cout << "|----------------------------------------|" << endl;
        	Song* current2 = temp.head;
        	if(current2 != nullptr)
        	{
        	
			do {
        	space = 40 - current2->title.size();
			cout << "| " << current2->title << setfill(' ') << setw(space) << "|" << endl;
            current2 = current2->next;
        	} while (current2 != temp.head);
    		}
        	cout << "|________________________________________|" << endl;
		
        int key = _getch();

        if (key == 224) {
            key = _getch();
            switch (key) {
                case 72: // Up arrow
                    if (selectedOption > 0) {
                        selectedOption--;
                    } else {
                        selectedOption = numOptions;
                    }
                    break;
                case 80: // Down arrow
                    if (selectedOption < numOptions) {
                        selectedOption++;
                    } else {
                        selectedOption = 0;
                    }
                    break;
            }
        } else if (key == 13) { // Enter key
            if (selectedOption == numOptions) {
            	PLM.Addplaylist(playlistName,temp);
                return; // Exit program
			} else {
                temp.addatTAIL(selected->title, selected->artist,selected->mood,selected->type);  
            }
        }
    }
}

void Show_playlists(int todo1,CircLL& songList){
	int selectedOption = 0;
    int numOptions = PLM.get_plcount(); // Use the count from CircLL
    clearScreen();
    playlist* current = PLM.get_plhead();
    playlist* selected = current;
	
    while (true) {
        top_title();
    	cout << "|========================================|" << endl;
    	cout << "|           Available Playlists          |" << endl;
    	cout << "|========================================|" << endl;
		
        // Display menu options with highlighted selection
        for (int i = 0; i < numOptions; ++i) {
        	//int maxY = getConsoleHeight() - 1;
            //setCursorPosition(0, min(numOptions + i, maxY));
            space = 39 - current->playlistName.size(); // total 40 spaces
            if (i == selectedOption) {
                cout << "| ";
                setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
                cout << current->playlistName << " ";
                setConsoleTextAttribute(FOREGROUND_GREEN);
                selected = current;
                cout << setfill(' ') << setw(space) << "|" << endl;
            } else {
                cout << "| ";
                cout << current->playlistName << " ";
                cout << setfill(' ') << setw(space) << "|" << endl;
            }
            current = current->link;
        }

        // Display Exit option after the last song
        //setCursorPosition(0, numOptions + numOptions);
        space = 40 - 6; // Total 40 spaces for "Exit"
        if (selectedOption == numOptions) {
            cout << "| ";
            setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
            cout << "[Back]";
            setConsoleTextAttribute(FOREGROUND_GREEN);
            cout << setfill(' ') << setw(space) << "|" << endl;
        } else {
            cout << "| ";
            cout << "[Back]";
            cout << setfill(' ') << setw(space) << "|" << endl;
        }

        cout << "|________________________________________|";
        cout << endl;

        int key = _getch();

        if (key == 224) {
            key = _getch();
            switch (key) {
                case 72: // Up arrow
                    if (selectedOption > 0) {
                        selectedOption--;
                    } else {
                        selectedOption = numOptions;
                    }
                    break;
                case 80: // Down arrow
                    if (selectedOption < numOptions) {
                        selectedOption++;
                    } else {
                        selectedOption = 0;
                    }
                    break;
            }
        } else if (key == 13) { // Enter key
            if (selectedOption == numOptions) {
                return; // Exit program
            } else {
            	CircLL t;
            	if(todo1==1)
                	update_playlist(selected,songList);
                else if(todo1==2)
                {
                	PLM.deletePlaylistNode(selectedOption+1);
                	numOptions = PLM.get_plcount();
                	current = PLM.get_plhead();
                	selected = current;
				}

            }
        }
    }
}
void playlist_menu(CircLL& songList)
{
	string sl[4];
    sl[0] = "[View All]";
    sl[1] = "[Add New]";
    sl[2] = "[Delete]";
    sl[3] = "[Back]";
		int size1 = sizeof(sl)/sizeof(sl[0]);
    	int selectedOption = 0;
		const int numOptions = size1;
		clearScreen();
    	while (true) {
        top_title();
        cout << "|                Playlist                |" << endl;
        cout << "|----------------------------------------|" << endl;
        for (int i = 0; i < numOptions; ++i) {
            space = 40 - sl[i].size();//total 40 spaces
            if (i == selectedOption)
			{
                cout << "| ";
				//system("COLOR A4");
                setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
                cout << sl[i] ;
                //system("COLOR 0A");
                setConsoleTextAttribute(FOREGROUND_GREEN);
                cout << setfill(' ') << setw(space) << "|" << endl;
            }
            else {
                cout << "| ";
                cout << sl[i] ;
                cout << setfill(' ') << setw(space) << "|" << endl;
            }
            //current = current->next;
        }
        cout << "|________________________________________|";
        cout << endl;

        int key = _getch();

        if (key == 224) {
            key = _getch();
            switch (key) {
            case 72: // Up arrow
            	if (selectedOption > 0) {
                    selectedOption--;
                }
                else
                {
                    selectedOption = numOptions - 1;
				}
                break;
            case 80: // Down arrow
                if (selectedOption < numOptions - 1) {
                    selectedOption++;
                }
                else
                {
                    selectedOption = 0;
				}
                break;
            }
        }
        else if (key == 13) { // Enter key
            if (selectedOption == numOptions - 1) {
                return; // Exit
            } else {
                clearScreen();
                if(selectedOption == numOptions - 1)
                	return;
                else
                {
                	switch(selectedOption)
					{
						case 0:
							Show_playlists(1,songList);
							break;
						case 1:
                        	Add_new_play(songList);
							break;
						case 2:
							Show_playlists(2,songList);
							break;
						case 3:
							return;
							break;
						
					}	
				}
            }
        }
}
}

void Options1(Song* selected)
{
		string sl[5];
    	sl[0] = "[>] Play ";
    	sl[1] = "[+] Add to Queue ";
    	sl[2] = "[=] Queue ";
    	sl[3] = "[!] Details ";
    	sl[4] = "[<] Back ";
    	int selectedOption = 0;
		const int numOptions = 5;
		clearScreen();
    	while (true) {
        top_title();
    	cout << "|                Options.                |" << endl;
    	cout << "|----------------------------------------|" << endl;
        for (int i = 0; i < numOptions; ++i) {
            space = 40 - sl[i].size();//total 40 spaces
            if (i == selectedOption)
			{
                cout << "| ";
				//system("COLOR A4");
                setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
                cout << sl[i];
                //system("COLOR 0A");
                setConsoleTextAttribute(FOREGROUND_GREEN);
                cout << setfill(' ') << setw(space) << "|" << endl;
            }
            else {
                cout << "| ";
                cout << sl[i];
                cout << setfill(' ') << setw(space) << "|" << endl;
            }
            //current = current->next;
        }
        cout << "|________________________________________|";
        cout << endl;

        int key = _getch();

        if (key == 224) {
            key = _getch();
            switch (key) {
            case 72: // Up arrow
            	if (selectedOption > 0) {
                    selectedOption--;
                }
                else
                {
                    selectedOption = numOptions - 1;
				}
                break;
            case 80: // Down arrow
                if (selectedOption < numOptions - 1) {
                    selectedOption++;
                }
                else
                {
                    selectedOption = 0;
				}
                break;
            }
        }
        else if (key == 13) { // Enter key
            if (selectedOption == numOptions - 1) {
                return; // Exit
            } else {
                switch(selectedOption)
				{
					case 0:
						songStack.push(selected);
						timer(selected->title,selected->artist);
						break;
					case 1:
						Q.enqueue(selected);
						//continue;
						break;
					case 2:
						play_queue();
						break;
					case 3:
						selected->details();
						break;	
				}
            }
        }
	}
}

void search_menu(CircLL& songList)
{
	string sl[5];
    sl[0] = "Name ";
    sl[1] = "Artist ";
    sl[2] = "Mood ";
    sl[3] = "Type ";
    sl[4] = "[Back]";
		int size1 = sizeof(sl)/sizeof(sl[0]);
    	int selectedOption = 0;
		const int numOptions = size1;
		clearScreen();
    	while (true) {
        top_title();
        cout << "|                 Search                 |" << endl;
        cout << "|----------------------------------------|" << endl;
        for (int i = 0; i < numOptions; ++i) {
            space = 40 - sl[i].size();//total 40 spaces
            if (i == selectedOption)
			{
                cout << "| ";
                setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
                cout << sl[i];
                setConsoleTextAttribute(FOREGROUND_GREEN);
                cout << setfill(' ') << setw(space) << "|" << endl;
            }
            else {
                cout << "| ";
                 cout << sl[i];
                cout << setfill(' ') << setw(space) << "|" << endl;
            }
        }
        cout << "|________________________________________|";
        cout << endl;

        int key = _getch();

        if (key == 224) {
            key = _getch();
            switch (key) {
            case 72: // Up arrow
            	if (selectedOption > 0) {
                    selectedOption--;
                }
                else
                {
                    selectedOption = numOptions - 1;
				}
                break;
            case 80: // Down arrow
                if (selectedOption < numOptions - 1) {
                    selectedOption++;
                }
                else
                {
                    selectedOption = 0;
				}
                break;
            }
        }
        else if (key == 13) { // Enter key
            if (selectedOption == numOptions - 1) {
                return; // Exit
            } else {
                clearScreen();
                searcher(songList,selectedOption+1);
            }
        }
}
}

void song_menu(CircLL& circLL) {
    int selectedOption = 0;
    int numOptions = circLL.get_count(); // Use the count from CircLL
    clearScreen();
    Song* current = circLL.head;
    Song* selected = current;
	
    while (true) {
        top_title();
        cout << "|               Song List                |" << endl;
        cout << "|----------------------------------------|" << endl;
		
        // Display menu options with highlighted selection
        space = 40 - 8;
        if (selectedOption == 0) {
            cout << "| ";
            setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
            cout << "[Search]";
            setConsoleTextAttribute(FOREGROUND_GREEN);
            cout << setfill(' ') << setw(space) << "|" << endl;
        } else {
            cout << "| ";
            cout << "[Search]";
            cout << setfill(' ') << setw(space) << "|" << endl;
        }
        for (int i = 1; i <= numOptions; ++i) {
        	//int maxY = getConsoleHeight() - 1;
            //setCursorPosition(0, min(numOptions + i, maxY));
        

            space = 39 - current->title.size(); 
			
            if (i == selectedOption) {
                cout << "| ";
                setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
                cout  << current->title << " ";
                setConsoleTextAttribute(FOREGROUND_GREEN);
                selected = current;
                cout << setfill(' ') << setw(space) << "|" << endl;
            } else {
                cout << "| ";
                cout  << current->title << " ";
                cout << setfill(' ') << setw(space) << "|" << endl;
            }
            current = current->next;
        }

        // Display Exit option after the last song
        //setCursorPosition(0, numOptions + numOptions);
        space = 40 - 6; // Total 40 spaces for "Exit"
        if (selectedOption == numOptions+1) {
            cout << "| ";
            setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
            cout << "[Back]";
            setConsoleTextAttribute(FOREGROUND_GREEN);
            cout << setfill(' ') << setw(space) << "|" << endl;
        } else {
            cout << "| ";
            cout << "[Back]";
            cout << setfill(' ') << setw(space) << "|" << endl;
        }

        cout << "|________________________________________|";
        cout << endl;

        int key = _getch();

        if (key == 224) {
            key = _getch();
            switch (key) {
                case 72: // Up arrow
                    if (selectedOption > 0) {
                        selectedOption--;
                    } else {
                        selectedOption = numOptions+1;
                    }
                    break;
                case 80: // Down arrow
                    if (selectedOption < numOptions+1) {
                        selectedOption++;
                    } else {
                        selectedOption = 0;
                    }
                    break;
            }
        } else if (key == 13) { // Enter key
            if (selectedOption == numOptions+1) {
                return; // Exit program
        	}else if(selectedOption ==0)
			{
				search_menu(circLL);
			} else {
                Options1(selected);
            }
        }
    }
}

void random_menu(CircLL& circLL)
{
	
	string sl[3];
    sl[0] = "";
    sl[1] = "[Suggest]";
    sl[2] = "[Back]";
	Song* temp = temp = getRandomSong(circLL);
	int size1 = sizeof(sl)/sizeof(sl[0]);
    int selectedOption = 0;
	const int numOptions = size1;
	clearScreen();			
    while (true) {
    	
        //clearScreen();
		//setConsoleTextAttribute(FOREGROUND_GREEN);
		
        top_title();
		space = 40 - temp->title.size();
		cout << "|              Random Song               |" << endl;
		cout << "|----------------------------------------|" << endl;
		sl[0]= "[Play] : " +  temp->title;
        for (int i = 0; i < numOptions; ++i) {
            //setCursorPosition(0, numOptions + i);
            space = 40 - sl[i].size();//total 40 spaces
            if (i == selectedOption) {
                cout << "| ";
				//system("COLOR A4");
                setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
                cout << sl[i];
                //system("COLOR 0A");
                setConsoleTextAttribute(FOREGROUND_GREEN);
                cout << setfill(' ') << setw(space) << "|" << endl;
            }
            else {
                cout << "| ";
                cout << sl[i];
                cout << setfill(' ') << setw(space) << "|" << endl;
            }
            //current = current->next;
        }
        cout << "|________________________________________|";
        cout << endl;

        int key = _getch();

        if (key == 224) {
            key = _getch();
            switch (key) {
            case 72: // Up arrow
            	if (selectedOption > 0) {
                    selectedOption--;
                }
                else
                {
                    selectedOption = numOptions - 1;
				}
                break;
            case 80: // Down arrow
                if (selectedOption < numOptions - 1) {
                    selectedOption++;
                }
                else
                {
                    selectedOption = 0;
				}
                break;
            }
        }
        else if (key == 13)// Enter key
		{ 
            switch(selectedOption)
			{
				case 0:
				timer(temp->title,temp->artist);
				songStack.push(temp);
    			break;
    			case 1:
					temp = getRandomSong(circLL);
    				break;
				case 2:
					return;
    				break;	
			}	
        }
    }
}

void most_played()
{
	Song* dash = songStack.mostPlayedSong();
	top_title();
	cout << "|              Most Played               |" << endl;
    cout << "|----------------------------------------|" << endl;
	
	if(dash==NULL)
	{
		cout << "|              No Favourite              |" << endl;
        //cout << "|________________________________________|";
	}
	else{	
    	space = 40 - dash->title.size();
		cout << "| " << dash->title << setfill(' ') << setw(space) << "|" << endl;
		//cout << "|________________________________________|";
	}
	
	cout << "|----------------------------------------|" << endl;;
	space = 40 - 6;
    cout << "| ";
    setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
    cout << "[Back]";
    setConsoleTextAttribute(FOREGROUND_GREEN);
    cout << setfill(' ') << setw(space) << "|" << endl;
    cout << "|________________________________________|";
    _getch();
}
void main_menu() 
{
	CircLL circLL;
    circLL.ReadAllSongs("All-Songs.txt");
    PLM.readAllPlaylistsFromFile();
    cout << "check1" <<endl;
	string sl[9];
	sl[0] = "[All Songs]";
    sl[1] = "[History]";
    sl[2] = "[Queue]";
    sl[3] = "[Most Played]";
    sl[4] = "[Random Song]";
    sl[5] = "[Playlist]";
    sl[6] = "[Sort]";
    sl[7] = "[Logout]";
    sl[8] = "[Exit]";
    cout << "check2" <<endl;
    songStack.loadHistoryFromFile();
    cout << "check3" <<endl;
	int size1 = sizeof(sl)/sizeof(sl[0]);
    int selectedOption = 0;
	const int numOptions = size1;
	cout << "check4" <<endl;
    //sl.artist[]
	//system("COLOR 0e");
	//clearScreen();
    while (true) {
    	
        //clearScreen();
		//setConsoleTextAttribute(FOREGROUND_GREEN);
        top_title();
        cout << "|                Main Menu               |" << endl;
        cout << "|----------------------------------------|" << endl;
        //cout << "|          Press Enter to Select         |" << endl;
        //cout << "|----------------------------------------|" << endl;
        // Display menu options with highlighted selection
        for (int i = 0; i < numOptions; ++i) {
            //setCursorPosition(0, numOptions + i);
            space = 40 - sl[i].size();//total 40 spaces
            if (i == selectedOption) {
                cout << "| ";
				//system("COLOR A4");
                setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
                cout << sl[i];
                //system("COLOR 0A");
                setConsoleTextAttribute(FOREGROUND_GREEN);
                cout << setfill(' ') << setw(space) << "|" << endl;
            }
            else {
                cout << "| ";
                cout << sl[i];
                cout << setfill(' ') << setw(space) << "|" << endl;
            }
            //current = current->next;
        }
        cout << "|________________________________________|";
        cout << endl;

        int key = _getch();

        if (key == 224) {
            key = _getch();
            switch (key) {
            case 72: // Up arrow
            	if (selectedOption > 0) {
                    selectedOption--;
                }
                else
                {
                    selectedOption = numOptions - 1;
				}
                break;
            case 80: // Down arrow
                if (selectedOption < numOptions - 1) {
                    selectedOption++;
                }
                else
                {
                    selectedOption = 0;
				}
                break;
            }
        }
        else if (key == 13) { // Enter key
                //clearScreen();
                	switch(selectedOption)
					{
						case 0:
							song_menu(circLL);
							break;
						case 1:
							//int f2;
                        	songStack.displayTimeline();
							break;
						case 2:
							play_queue();
							break;
						case 3:
							most_played();
							break;
						case 4:
							random_menu(circLL);
							break;
						case 5:
							{
								
								playlist_menu(circLL);
								PLM.writeAllPlaylistsToFile();
							}
							break;
						case 6:
							insertionSort(circLL);
							circLL.writeAllSongs("All-Songs.txt");
							break;
						case 7:
							songStack.saveHistoryToFile();
							return;
							break;
						case 8:
							songStack.saveHistoryToFile();
							exit(1);
							break;
						
					}	
            }
    }
}
void Signup()
{
	
	string sl[3];
	sl[0] = "[Login]";
    sl[1] = "[Register]";
    sl[2] = "[Back]";
	UserInfo user;
	int size1 = sizeof(sl)/sizeof(sl[0]);
    int selectedOption = 0;
	const int numOptions = size1;
    //sl.artist[]
	//system("COLOR 0e");
	clearScreen();
    while (true) {
    	
        //clearScreen();
		//setConsoleTextAttribute(FOREGROUND_GREEN);
        top_title();
    	cout << "|                Register                |" << endl;
		cout << "|----------------------------------------|" << endl;
        //cout << "|          Press Enter to Select         |" << endl;
        //cout << "|----------------------------------------|" << endl;
        // Display menu options with highlighted selection
        for (int i = 0; i < numOptions; ++i) {
            //setCursorPosition(0, numOptions + i);
            space = 40 - sl[i].size();//total 40 spaces
            if (i == selectedOption) {
                cout << "| ";
				//system("COLOR A4");
                setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
                cout << sl[i];
                //system("COLOR 0A");
                setConsoleTextAttribute(FOREGROUND_GREEN);
                cout << setfill(' ') << setw(space) << "|" << endl;
            }
            else {
                cout << "| ";
                cout << sl[i];
                cout << setfill(' ') << setw(space) << "|" << endl;
            }
            //current = current->next;
        }
        cout << "|________________________________________|";
        cout << endl;

        int key = _getch();

        if (key == 224) {
            key = _getch();
            switch (key) {
            case 72: // Up arrow
            	if (selectedOption > 0) {
                    selectedOption--;
                }
                else
                {
                    selectedOption = numOptions - 1;
				}
                break;
            case 80: // Down arrow
                if (selectedOption < numOptions - 1) {
                    selectedOption++;
                }
                else
                {
                    selectedOption = 0;
				}
                break;
            }
        }
        else if (key == 13) { // Enter key
                //clearScreen();
                switch(selectedOption)
				{
					case 0:
						if( user.signIn("user_info.txt"))
						{
							main_menu();
						}
						break;
					case 1:
					{
						string input;
						string input2;
    					cout << "  Enter First Name: ";
    					//cin.ignore(); // Ignore newline character left in the buffer
    					fflush(stdin);
    					cin >> input;
    					cout << "  Enter Last Name: ";
    					cin >> input2;
						user.setName(input+"-"+input2);
    					cout << "  Enter Username: ";
    					cin >> input;
						user.setUsername(input);

    					cout << "  Enter Password: ";
    					input = user.Hide_pass();
    					cout << "\n  Show Password(1.Yes, 2.No):\n  => ";
    					int pk;
    					cin >> pk;
    					if (pk == 1)
        					cout << "  Password: " << input << endl << endl ;
    					//cin >> input;
						user.setPassword(input);

    					cout << "  Enter Favorite Genre (e.g.Rock): ";
    					fflush(stdin);
    					cin >> input;
    					user.setMusicPlayerInfo(input);
    					// Write user info to file
    					user.writeUserInfo("user_info.txt");
						int db;
						db=_getch();
						break;
						}
					case 2:
						return;
						break;
					
				}	
            }
    	}
}


int main() {
    Signup();
}
//22k-4336 | 22k-4312 | 22k-4613