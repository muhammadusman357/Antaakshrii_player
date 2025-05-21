// CPP program to create a timer
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <iomanip> // for setw()
#include <fstream>
#include <sstream>
//#include <string.h>
#include <conio.h>// for _khbit,getch
#include <stdlib.h>
//#include <unistd.h>
//#include <thread>
//#include <chrono>
#include <mmsystem.h>
#include <cmath>

#pragma comment(lib, "winmm.lib")
using namespace std;
int ti = 0;
// hours, minutes, seconds of timer
//int hours = 0;
int minutes = 0;//current minutes,
int seconds = 0;//current seconds
int m=0,s=0;// total minutes,seconds
int songDuration;
int h1=0,h2=0,h3=0,a=0;
int playersize = 25;
string Lyricsstr,str3,str4,Artist,Album;
int curentvolume=100;
int word_count=0;
bool isPlaying = false;
bool shouldExit = false;  // Flag to control program exit
void Loading2()
{
	
    //system("COLOR 0e");
    
    //system("cls");
    cout << "\e[?25l";

    //Set ASCII to print special character.
    //Code page 437
    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    int bar1 = 177, bar2 = 219;
    
    double percentage = ((double)(h1) / h2) * 100;
    int loopEndLimit = (percentage / 100) * playersize;
    int k=playersize-loopEndLimit;
    cout << "|";
    int j = (h1+1)/6;
    int j2 = (h2+1)/6;
    //int k = j2-j;
    if(minutes==0 && seconds==0)
    {
    	//for(int i = 0 ; i <= k; i++)
        	cout << "                          ||";
	}	
    else
    {
    	
    	for(int i = 0; i <= loopEndLimit; i++)
    	{
        	cout << (char)bar2;
        	
    	}
    	for(int i = 0 ; i < k; i++)
    	{
        	cout << " ";
    	}
   	
    	cout << "||";

    }
    

}

void playAudio(const char* audioFile)
{
    MCI_OPEN_PARMS mciOpen;
    mciOpen.lpstrElementName = audioFile;

    if (mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD_PTR)&mciOpen) != 0)
	{
        cerr << "Error opening the audio file" << endl;
        return;
    }

    MCI_PLAY_PARMS mciPlay;
    if (mciSendCommand(mciOpen.wDeviceID, MCI_PLAY, 0, (DWORD_PTR)&mciPlay) != 0) {
        cerr << "Error playing the audio" << endl;
        mciSendCommand(mciOpen.wDeviceID, MCI_CLOSE, 0, 0);
    }
}

void pauseAudio() {
    mciSendString("pause all", nullptr, 0, nullptr);
}

void resumeAudio() {
    mciSendString("resume all", nullptr, 0, nullptr);
}

void setVolume(int percentage) {
    // Ensure the volume is within the valid range (0-100)
    int clampedPercentage = max(0, min(100, percentage));

    // Calculate the volume in a format accepted by waveOutSetVolume
    DWORD volume = DWORD(std::round((clampedPercentage / 100.0) * 0xFFFF));

    // Set the system-wide volume
    if (waveOutSetVolume(0, volume) != MMSYSERR_NOERROR) {
        cerr << "Error setting system volume" << endl;
    }
}






// Function to forward the audio to a specific time interval
void forwardAudio(const char* audioFile, int minutes, int seconds, int songDuration) {
    int totalSeconds = minutes * 60 + seconds;

    if (totalSeconds >= songDuration) {
        cerr << "Invalid time. Cannot skip beyond the end of the audio." << endl;
        return;
    }

    // Close the currently playing audio
    mciSendString("close all", nullptr, 0, nullptr);

    // Reopen the audio file
    MCI_OPEN_PARMS mciOpen;
    mciOpen.lpstrElementName = audioFile;
    if (mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD_PTR)&mciOpen) != 0) {
        cerr << "Error opening the audio file" << endl;
        return;
    }

    // Seek to the desired position
    MCI_SEEK_PARMS mciSeek;
    mciSeek.dwTo = totalSeconds * 1000;
    if (mciSendCommand(mciOpen.wDeviceID, MCI_SEEK, MCI_TO, (DWORD_PTR)&mciSeek) != 0) {
        cerr << "Error seeking to the specified time" << endl;
        return; // Stop further execution if seeking fails
    }

    // Play the audio from the new position
    MCI_PLAY_PARMS mciPlay;
    if (mciSendCommand(mciOpen.wDeviceID, MCI_PLAY, 0, (DWORD_PTR)&mciPlay) != 0) {
        cerr << "Error playing the audio" << endl;
    }
}

// Function to calculate the duration of a song
int GetSongDuration(const string& audioFile) {
	int songDuration;


    // Open the audio file to get its duration
    MCI_OPEN_PARMS mciOpenForDuration;
    mciOpenForDuration.lpstrElementName = audioFile.c_str();
    if (mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD_PTR)&mciOpenForDuration) == 0) {
        MCI_STATUS_PARMS mciStatus;
        mciStatus.dwItem = MCI_STATUS_LENGTH;
        if (mciSendCommand(mciOpenForDuration.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&mciStatus) == 0) {
            songDuration = mciStatus.dwReturn;
        } else {
            songDuration = 0; // Unable to retrieve duration
        }
        mciSendCommand(mciOpenForDuration.wDeviceID, MCI_CLOSE, 0, 0);
    } else {
        cerr << "Error opening the audio file" << endl;
        return 0;
    }

    if (songDuration == 0) {
        cerr << "Unable to retrieve the song duration. Skipping time will not work correctly." << endl;
    }
    return songDuration;

}

void player1(string audioFile) {
    
    int songDuration;


    // Open the audio file to get its duration
    MCI_OPEN_PARMS mciOpenForDuration;
    mciOpenForDuration.lpstrElementName = audioFile.c_str();
    if (mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD_PTR)&mciOpenForDuration) == 0) {
        MCI_STATUS_PARMS mciStatus;
        mciStatus.dwItem = MCI_STATUS_LENGTH;
        if (mciSendCommand(mciOpenForDuration.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&mciStatus) == 0) {
            songDuration = mciStatus.dwReturn;
        } else {
            songDuration = 0; // Unable to retrieve duration
        }
        mciSendCommand(mciOpenForDuration.wDeviceID, MCI_CLOSE, 0, 0);
    } else {
        cerr << "Error opening the audio file" << endl;
        return;
    }

    if (songDuration == 0) {
        cerr << "Unable to retrieve the song duration. Skipping time will not work correctly." << endl;
    }

    //char command;
    int minutes, seconds;

    // Play the audio
    playAudio(audioFile.c_str());

    return;
}


const int FRAME_WIDTH = 40; // Set the desired frame width

vector<string> lastDisplayedLyrics;

void displayLyrics(const string& filePath, int currentMinutes, int currentSeconds) {
    ifstream file(filePath);
    vector<string> words;

    if (!file.is_open()) {
        cerr << "|         Lyrics not available           |" << endl;
        cout  <<"|________________________________________|" << endl;
        return;
    }

    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        int minutes1, seconds1;
        char delimiter;
        string lyrics;
        string word;

        if (iss >> minutes1 >> delimiter >> seconds1) {
            getline(iss >> ws, lyrics);

            if (minutes1 == currentMinutes && seconds1 == currentSeconds) {
                istringstream lyricsStream(lyrics);
				word_count=0;
                while (lyricsStream >> word) {
                	word_count++;
                    words.push_back(word);
                }

                lastDisplayedLyrics = words;

                // Display lyrics within the frame width
                int remainingWidth = FRAME_WIDTH;
    			cout << "|";
    			for (const auto& w : words) {
    				if (w.length() + 1 <= remainingWidth) {
    					cout << " " << w;
    					remainingWidth -= w.length() + 1;
    				} else {
    					int space2 = remainingWidth;
            			cout << setfill(' ') << setw(remainingWidth+1) << "|" << endl;
            			cout << "| " << w;
            			remainingWidth = FRAME_WIDTH - w.length() - 1;
        			}
    			}

    			cout << setfill(' ') << setw(remainingWidth+1) << "|";
    			cout << endl;
                cout  <<"|________________________________________|" << endl;
                return;
            }
        }
    }
	file.close();
    if (!lastDisplayedLyrics.empty()) {
        int remainingWidth = FRAME_WIDTH;
		cout << "|";
    	for (const auto& w : lastDisplayedLyrics) {
    		if (w.length() + 1 <= remainingWidth) {
    			cout << " " << w;
    			remainingWidth -= w.length() + 1;
    		} else {
    			int space2 = remainingWidth;
            	cout << setfill(' ') << setw(remainingWidth+1) << "|" << endl;
            	cout << "| " << w;
            	remainingWidth = FRAME_WIDTH - w.length() - 1;
        	}
    	}

    	cout << setfill(' ') << setw(remainingWidth+1) << "|";
    	cout << endl;
        cout << "|________________________________________|" << endl;
    } else{
        cout  <<"|________________________________________|" << endl;
    }
}
void menu(int m,int s)
{
	
        
        // Check for keyboard input
        if (_kbhit()){
            char input = _getch();
            switch (input) {
                case '1':
                	if(minutes==0 && seconds==0)
                		player1(str4);
                	else if(isPlaying)
                		pauseAudio();
                	else
                		resumeAudio();
                	
                    isPlaying = !isPlaying; // Toggle play/pause
                    break;
                case '2':
                    // Reset the timer
                    minutes = seconds = 0;
                    isPlaying = true;
                    forwardAudio(str4.c_str(), minutes, seconds, songDuration);
                    break;
                case '3':
                	pauseAudio();
                    cout << endl << "Enter minutes: ";
                    cin >> minutes;
                    while(minutes>m)
					{
						cout << "Entered minutes is greater than maximum song limit!"<< endl;
						cout << "Enter minutes: ";
						cin >> minutes;
					}
                    cout << "Enter seconds: ";
                    cin >> seconds;
                    while(seconds>59)
					{
						cout << "Invalid value"<< endl;
						cout << "Enter Seconds: ";
						cin >> seconds;

					}
                    while(minutes==m && seconds>s)
					{
							cout << "value should be <= " << s << endl;
							cout << "Enter Seconds: ";
							cin >> seconds;
					}
					forwardAudio(str4.c_str(), minutes, seconds, songDuration);
					isPlaying = false;
					pauseAudio();
                    break;
                case '4':
                	curentvolume+=10;
                	if(curentvolume>100)
                		curentvolume=100;
                	setVolume(curentvolume);
                	break;
                case '5':
                	
                	curentvolume-=10;
                	if(curentvolume<0)
                		curentvolume=0;
                	setVolume(curentvolume);
                	break;
                case '6':
                	mciSendString("close all", nullptr, 0, nullptr);
                    shouldExit=true;
					break; // Exit the program
            }
        }       
}
void setConsoleTextAttribute(WORD attributes);
// function to display the timer
void displayClock(int m,int s,string str)
{
	// system call to clear the screen
	system("COLOR 0A");
	system("cls");
	//setConsoleTextAttribute(FOREGROUND_RED | BACKGROUND_GREEN);
	h3 = 15 + playersize;
	//for(int i=0;i<h3;i++)
	//cout << " ________________________________________" << endl;
	cout << "|========================================|";
	cout << endl << "|" << setfill(' ') << setw(25) <<"Antakshri"<< setw(16) << setfill(' ') << setw(16) << "|" << endl;
	//for(int i=0;i<h3;i++)
	cout << "|========================================|";
	cout << endl << "|" << "\tNow Playing: ";
	int screenWidth = 11;
	int textWidth = str.length();
	if((minutes==0 && seconds==0) || (minutes==m && seconds==s))
	{
		for(int tj = 0; tj < screenWidth; tj++)
		{
			cout <<str[tj];
		}
	}
	else
	{
		if(ti>=textWidth)
		{
			ti=0;
		}
        for (int tj = 0; tj < screenWidth; ++tj)
		{
            int index = (ti + tj) % textWidth;
            cout << str[index];
        }

	ti++;
	}
	int space,digit;
	cout << setfill(' ') << setw(10) << "|" << endl;
	//for(int i=0;i<h3;i++)
	cout << "|----------------------------------------|";
	cout << endl;
	cout << "| Music: " << (isPlaying ? "Playing" : "Paused");
	if(curentvolume==100)
	{
		digit = 3;
		space = 2;
	}
	else if(curentvolume==0)
	{
		space = 4;
		digit = 1;
	}
	else
	{
		space = 3;
		digit = 2;
	}
		
	if(isPlaying)
		cout << setfill(' ') << setw(20) << "Volume: " << setfill('0') << setw(digit) << curentvolume << "%" << setfill(' ') << setw(space) << "|" << endl;
	else
		cout << setfill(' ') << setw(21) << "Volume: " << setfill('0') << setw(digit) << curentvolume << "%" << setfill(' ') << setw(space) << "|" << endl;
	cout << "|----------------------------------------|";
	cout << endl;
	//cout << setfill(' ') << setw(29);
	cout << "|" << setfill('0') << setw(2) << minutes << ":";
	cout << setfill('0') << setw(2) << seconds;
	cout << "/" << setfill('0') << setw(2) << m << ":";
	cout << setfill('0') << setw(2) << s << " ";
	Loading2();
	cout << endl;
	//for(int i=0;i<h3;i++)
	cout << "|----------------------------------------|";
	cout << endl;
	// Display menu
    cout << "| Menu:" << setfill(' ') << setw(35) << "|" << endl;
    cout << "| 1. " << (isPlaying ? "[Pause]" : "[Play]"); 
	if(isPlaying)
		cout << setfill(' ') << setw(30) << "|" << endl;
	else
		cout << setfill(' ') << setw(31) << "|" << endl;
    cout << "| 2. [Replay]" << setfill(' ') << setw(29) << "|" << endl;
    cout << "| 3. [Skip]" << setfill(' ') << setw(31) << "|" << endl;
    cout << "| 4. [Vol++]" << setfill(' ') << setw(30) << "|" << endl;
    cout << "| 5. [Vol--]" << setfill(' ') << setw(30) << "|" << endl;
    cout << "| 6. [Exit]" << setfill(' ') << setw(31) << "|" << endl;
	cout << "|----------------------------------------|"<< endl;
	cout << "|  ***************Enjoy!***************  |"<< endl;
	cout << "|----------------------------------------|" << endl;
	//cout << "| ";
	displayLyrics(Lyricsstr,minutes,seconds);
	
	//setConsoleTextAttribute(FOREGROUND_INTENSITY);
	//sleep(1);
    Sleep(1000);
}

void timer(string str,string str2)
{
	// infinite loop because timer will keep 
	// counting. To kill the process press
	// Ctrl+D. If it does not work ask
	// ubuntu for other ways.
	setVolume(curentvolume);
	minutes=0;
	seconds=0;
    shouldExit=0;
    Artist = str2;
    Lyricsstr = str + ".txt";
	str3 = str + " by " + str2 + " ";
	str4 = str + ".wav";
	songDuration = GetSongDuration(str4);
	int songDuration2 = GetSongDuration(str4);
	m = (songDuration/1000)/60;
	s = (songDuration/1000)-(m*60);
	
	while (true) 
	{
		h2 = s+(60*m);
		if (shouldExit) {
			minutes=0;
			seconds=0;
			isPlaying = false;
			system("cls");
            return;
        }
		if(h1>=h2)
		{	
			displayClock(m,s,str3);
			isPlaying = false;
			//shouldExit=true;
			menu(m,s);
		}
		else
		{
		displayClock(m,s,str3);
		
        // Update the timer
        if (isPlaying) {
            if (++seconds >= 59) {
                seconds = 0;
                if ((minutes == m && seconds >= s)  || ++minutes > m) {
                    isPlaying = false;
                    minutes = m;
                    seconds = s;
                }
            }
        }
        menu(m,s);
	 	}
		//sleep(1);
		
		h1 = seconds+(60*minutes);
		
		
	}
}

struct songlist
{
	string SongName;
	string artist;	
};

void clearScreen() {
    system("cls");
}
void setConsoleTextAttribute(WORD attributes) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attributes);
}

/*void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}



int getConsoleHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}*/

/*int main()
{
	songlist sl[5];
	sl[0].SongName="Tu-Hai-Kahan";
    sl[0].artist = "AUR";
	sl[1].SongName="Long-Time-No-See";
	sl[1].artist = "Taimour Baig, Raffey Anwar & AUR";
	sl[2].SongName="Memories";
	sl[2].artist = "Maroon 5";
	sl[3].SongName="Ae-Meri-Zohra-Jabeen";
	sl[3].artist = "Manna Dey";
	sl[4].SongName= "Exit";
	string mt = "Antakshri";
	int size1 = sizeof(sl)/sizeof(sl[0]);
	song_menu(sl,mt,size1);
	
}*/
