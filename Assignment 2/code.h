// Zohaib Adnan
// 19i-0741
// Data Structures
// Assignment 2

#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//**************** Class Prototypes ****************//

template <typename T1, typename T2, typename T3>
class MMD; // Music Metadata Database
template <typename T1, typename T2>
class AMD; // Author Metadata Database
template <typename T1, typename T2, typename T3>
class AD; // Album Database
template <typename T1>
class ADP; // Author Discography Playlist
template<typename T1>
class Tracks;
template<typename T1>
class Albums;

//**************** Function Prototypes ****************//

// Database Creation Functions
template <typename T1, typename T2, typename T3>
MMD<T1, T2, T3>* Create_MMD(string path); // Returns the head of the MMD linked list
template <typename T1, typename T2>
AMD<T1, T2>* Create_AMD(string path); // Returns the head of the AMD linked list
template <typename T1, typename T2, typename T3>
AD<T1, T2, T3>* Create_AD(string path); // Returns the head of the AD linked list
template<typename T1>
ADP<T1>* Create_ADP(string path); // Returns the head of the ADP linked list

// Search Functions
template<typename T1, typename T2, typename T3>
MMD<T1, T2, T3>* Search_Music(int MBID); // Searches for song by MBID
template<typename T1, typename T2>
AMD<T1, T2>* Search_Author(int AID); // Searches for author by AID
template<typename T1, typename T2, typename T3>
AD<T1, T2, T3>* Search_Album(int ABID); // Searches for album by ABID
template<typename T1>
ADP<T1>* Search_Discography(int DID); // Searches for discography playlist by DID
template<typename T1>
Tracks<T1>* Search_Music_By_Album(int ABID); // Searches for tracks list by album (ABID)
template<typename T1>
Albums<T1>* Search_Music_By_Author(int DID); // Searches for albums list by discography playlist (DID)


//**************** Global Objects ****************//

MMD<int, string, float>* mmdHead = NULL; // MMD linked list head
AMD<int, string>* amdHead = NULL; // AMD linkedlist head
AD<int, string, float>* adHead = NULL; // AD linked list head
ADP<int>* adpHead = NULL; // ADP linked list head

//**************** Classes ****************//

//Music Metadata DataBase (A doubly linked list)
template <typename T1, typename T2, typename T3>
class MMD
{
public:
	// Data members
	T1 mbid;
	T2 songName;
	T2 writer;
	T3 length;

	AD<T1, T2, T3>* album;

	// Connections
	MMD* next;
	MMD* previous;
};

//Author Metadata DataBase (A circular linked list)
template <typename T1, typename T2>
class AMD
{
public:
	// Data members
	T1 aid;
	T2 name;
	T2 band;
	T2 gender;
	T2 dob;
	T2 date;
	T2 genre;

	AD<T1, T2, float>* albums;
	ADP<T1>* adp;

	// Connections
	AMD* next;

	AMD() // A constructor to initialise the albums pointer
	{
		albums = NULL;
	}
};

//Tracks (A singly linked list)
template <typename T1>
class Tracks
{
public:
	// Data members
	T1 trackNumber;

	MMD<int, string, float>* trackRef;

	// Connections
	Tracks* next;
};

//Album DataBase (A circular linked list)
template <typename T1, typename T2, typename T3>
class AD
{
public:
	// Data members
	T1 abid;
	T2 albumName;
	T2 publisher;
	T1 numTracks;
	T3 totDur;

	AMD<T1, T2>* author;
	Tracks<T1>* tracks;
	ADP<T1>* adp;

	// Connections
	AD* next;
};

//Albums (A singly linked list)
template<typename T1>
class Albums
{
public:
	// Data members
	T1 year;

	AD<int, string, float>* albumRef;

	// Connections
	Albums* next;
};

//Author Discography Playlist (A circular linked list)
template<typename T1>
class ADP
{
public:
	// Data members
	int did;
	AMD<T1, string>* author;
	Albums<T1>* albums;

	// Connections
	ADP* next;

	ADP() // A constructor to initialise the albums pointer
	{
		albums = NULL;
	}
};

//**************** Functions ****************//

template <typename T1, typename T2, typename T3>
MMD<T1, T2, T3>* Create_MMD(string path)
{
	ifstream iFile;
	iFile.open(path);
	if (iFile.is_open()) // Ensure that the input file is open
	{
		string str, subStr; // A main string and a substring
		int index; // Keeps track of the last accessed position of the str string
		MMD<T1, T2, T3>* currNode = mmdHead; 
		MMD<T1, T2, T3>* prevNode = mmdHead;
		getline(iFile, str); // Discard the first line of data
		while(getline(iFile, str)) // Retreive the next line of data
		{	
			currNode = new MMD<T1, T2, T3>;
			index = 0; // Reset the index variable
			subStr = ""; // Clear the subStr string
			while (str[index] != ',') // Separate the MBID from the str string
			{
				subStr += str[index];
				index++;
			}
			currNode->mbid = stoi(subStr);
			index++;
			subStr = "";
			while (str[index] != ',') // Separate the song name from the str string
			{
				if (str[index] == '\"') // A special condition for MBID 100
				{
					index++;
					while (str[index] != '\"')
					{
						subStr += str[index];
						index++;
					}
				}
				else
					subStr += str[index];
				index++;
			}
			currNode->songName = subStr;
			index++;
			subStr = "";
			while (str[index] != ',') // Separate the writer from the str string
			{
				subStr += str[index];
				index++;
			}
			currNode->writer = subStr;
			index++;
			subStr = "";
			while (str[index] != '\0') // Separate the length from the str string
			{
				subStr += str[index];
				index++;
			}
			currNode->length = stof(subStr);
			if (mmdHead == NULL) // The MMD linked list is currently empty
			{
				mmdHead = currNode; // Directly add the current node at the very front of the linked list
				currNode->previous = mmdHead;
				currNode->next = NULL;
			}
			else // The MMD linked list is currently not empty
			{
				prevNode->next = currNode; // Add the current node after the previous node
				currNode->previous = prevNode;
				currNode->next = NULL;
			}
			prevNode = currNode;
		}
		iFile.close();
		return mmdHead;
	}
	cout << "Error creating the Music Metadata Database! The Music.csv file could not be opened." << endl;
	return NULL;
}

template <typename T1, typename T2>
AMD<T1, T2>* Create_AMD(string path)
{
	ifstream iFile;
	iFile.open(path);
	if (iFile.is_open())
	{
		string str, subStr; // A main string and a substring
		int index; // Keeps track of the last accessed position of the str string
		AMD<T1, T2>* currNode = amdHead;
		AMD<T1, T2>* prevNode = amdHead;
		getline(iFile, str); // Discard the first line of data
		while (getline(iFile, str)) // Retrieve the next line of data
		{
			currNode = new AMD<T1, T2>;
			index = 0; // Reset the index variable
			subStr = ""; // Clear the subStr string
			while (str[index] != ',') // Separate the AID from the str string
			{
				subStr += str[index];
				index++;
			}
			currNode->aid = stoi(subStr);
			index++;
			subStr = "";
			while (str[index] != ',') // Separate the name from the str string
			{
				subStr += str[index];
				index++;
			}
			currNode->name = subStr;
			index++;
			subStr = "";
			while (str[index] != ',') // Separate the band from the str string
			{
				subStr += str[index];
				index++;
			}
			currNode->band = subStr;
			index++;
			subStr = "";
			while (str[index] != ',') // Separate the gender from the str string
			{
				subStr += str[index];
				index++;
			}
			currNode->gender = subStr;
			index++;
			subStr = "";
			while (str[index] != ',') // Separate the date of birth from the str string
			{
				subStr += str[index];
				index++;
			}
			currNode->dob = subStr;
			index++;
			subStr = "";
			while (str[index] != ',') // Separate the date from the str string
			{
				subStr += str[index];
				index++;
			}
			currNode->date = subStr;
			index++;
			subStr = "";
			while (str[index] != '\0') // Separate the genre from the str string
			{
				subStr += str[index];
				index++;
			}
			currNode->genre = subStr;
			if (amdHead == NULL) // The AMD linked list is currently empty
			{
				amdHead = currNode; // Add the current node at the very front of the linked list
				currNode->next = NULL;
			}
			else // The AMD linked list is currently not empty
			{
				prevNode->next = currNode; // Add the current node after the previous node
				currNode->next = NULL;
			}
			prevNode = currNode;
		}
		currNode->next = amdHead; // Complete circular connection
		iFile.close();
		return amdHead;
	}
	cout << "Error creating the Author Metadata Database! The Authors.csv file could not be opened." << endl;
	return NULL;
}

template <typename T1, typename T2, typename T3>
AD<T1, T2, T3>* Create_AD(string path)
{
	ifstream iFile;
	iFile.open(path);
	if (iFile.is_open())
	{
		string str, subStr; // A main string and a substring
		int index; // Keeps track of the last accessed location of the str string
		AD<T1, T2, T3>* currNode = adHead;
		AD<T1, T2, T3>* prevNode = adHead;
		getline(iFile, str); // Discard the first line of data
		while (getline(iFile, str)) // Retrieve the next line of data
		{
			currNode = new AD<T1, T2, T3>;
			index = 0; // Reset the index variable
			subStr = ""; // Clear the subStr string
			while (str[index] != ',') // Separate the ABID from the str string
			{
				subStr += str[index];
				index++;
			}
			currNode->abid = stoi(subStr);
			index++;
			subStr = "";
			while (str[index] != ',') // Separate the album name from the str string
			{
				subStr += str[index];
				index++;
			}
			currNode->albumName = subStr;
			index++;
			subStr = "";
			while (str[index] != ',') // Separate the AID from the str string
			{
				subStr += str[index];
				index++;
			}
			int aid = stoi(subStr);
			AMD<T1, T2>* temp = amdHead; 
			while (temp->aid != aid) // Find the author in the AMD linked list with the current AID 
				temp = temp->next;
			currNode->author = temp;
			index++;
			subStr = "";
			while (str[index] != ',') // Separate the publisher from the str string
			{
				subStr += str[index];
				index++;
			}
			currNode->publisher = subStr;
			index++;
			subStr = "";
			while (str[index] != ',') // Separate the number of tracks from the str string
			{
				subStr += str[index];
				index++;
			}
			currNode->numTracks = stoi(subStr);
			index++;
			subStr = "";
			while (str[index] != ',') // Separate the total duration from the str string
			{
				subStr += str[index];
				index++;
			}
			currNode->totDur = stof(subStr);
			index++;
			subStr = "";
			Tracks<T1>* currTrack = currNode->tracks;
			Tracks<T1>* prevTrack = currNode->tracks;
			for (int count = 1; count <= currNode->numTracks; count++) // The length of the tracks linked list for each album depends on the number of tracks in that album
			{
				currTrack = new Tracks<T1>;
				subStr = "";
				while (str[index] != ',') // Separate the track number from the str string
				{
					subStr += str[index];
					index++;
				}
				currTrack->trackNumber = stoi(subStr);
				index++;
				subStr = "";
				while (str[index] != '\0') // Separate the track MBID from the str string
				{
					subStr += str[index];
					index++;
				}
				// Two-way linking between the AD and the MMD
				int mbid = stoi(subStr);
				MMD<T1, T2, T3>* temp = mmdHead; // Find the song in the MMD playlist with the current MBID
				while (temp->mbid != mbid)
					temp = temp->next;
				currTrack->trackRef = temp;
				temp->album = currNode; // The currently selected song in the MMD linked list should point to this (the current) album
				if (count == 1) // The tracks linked list for the current album is currently empty
				{
					currNode->tracks = currTrack; // Add the current track at the very front of the tracks linked list
					currTrack->next = NULL;
				}
				else // The tracks linked list for the current album is not currently empty
				{
					prevTrack->next = currTrack; // Add the current track after the previous track
					currTrack->next = NULL;
				}
				prevTrack = currTrack;
				if (count == currNode->numTracks) // Do not retrieve the next line of data if all the tracks for the current album have already been added
					break;
				getline(iFile, str); // Retreive the next track for the current album
				index = 0;
				// Discard the ABID, album, AID, publisher, number of tracks, and total duration
				// Because we are still adding tracks to the same album
				while (str[index] != ',')  // Discard the ABID
				{
					subStr += str[index];
					index++;
				}
				index++;
				while (str[index] != ',') // Discard the album
				{
					subStr += str[index];
					index++;
				}
				index++;
				while (str[index] != ',') // Discard the AID
				{
					subStr += str[index];
					index++;
				}
				index++;
				while (str[index] != ',') // Discard the publisher
				{
					subStr += str[index];
					index++;
				}
				index++;
				while (str[index] != ',') // Discard the number of tracks
				{
					subStr += str[index];
					index++;
				}
				index++;
				while (str[index] != ',') // Discard the total duration
				{
					subStr += str[index];
					index++;
				}
				index++;
			}
			// Two-way linking between the AD and the AMD
			AMD<T1, T2>* currAuthor = amdHead; 
			while (currAuthor->aid != aid)
				currAuthor = currAuthor->next; // Traverse the AMD list until the author with the current AID is found
			AD<T1, T2, T3>* newAlbum = new AD<T1, T2, T3>;
			*newAlbum = *currNode; // Copy the current album data that was read from the input file for the selected author
			if (currAuthor->albums == NULL) // No albums for the selected author have been added yet
			{
				currAuthor->albums = newAlbum; // Add the current album at the very front
				newAlbum->next = currAuthor->albums;
			}
			else // Albums for the current author have previously been added
			{
				AD<T1, T2, T3>* currAlbum = currAuthor->albums; // Find the last album that was added for the selected author
				while(currAlbum->next != currAuthor->albums)
					currAlbum = currAlbum->next;
				currAlbum->next = newAlbum; // Add the current album after this last album
				newAlbum->next = currAuthor->albums;
			}
			if (adHead == NULL) // The AD linked list is currently empty
			{
				adHead = currNode; // Add the current node at the very front of the AD linked list
				currNode->next = NULL;
			}
			else // The AD linked list is not currently empty
			{
				prevNode->next = currNode; // Add the current node after the previous node
				currNode->next = NULL;
			}
			prevNode = currNode;
		}
		currNode->next = adHead; // Complete circular connection
		iFile.close();
		return adHead;
	}
	cout << "Error creating the Album Database! The Albums.csv file could not be opened." << endl;
	return NULL;
}

template<typename T1>
ADP<T1>* Create_ADP(string path)
{
	ifstream iFile;
	iFile.open(path);
	if (iFile.is_open())
	{
		string str, subStr; // A main string and a substring
		int index; // Keeps track of the last accessed location of the str string
		ADP<T1>* currNode = adpHead;
		ADP<T1>* prevNode = adpHead;
		int prevDID = -1; // Used to ensure that only one discography playlist is made for each author (since the DID for each author is the same as their AID)
		getline(iFile, str); // Discard the first line of data
		while (getline(iFile, str)) // Retrieve the next line of data
		{
			bool flag = false; // This flag is used along with the prevDID variable
			index = 0; // Reset the index variable
			subStr = ""; // Clear the subStr string
			while (str[index] != ',') // Separate the DID from the str string
			{
				subStr += str[index];
				index++;
			}
			if (stoi(subStr) != prevDID) // Create a new node when the DID changes
			{
				currNode = new ADP<T1>;
				currNode->did = stoi(subStr);
				flag = true;
				prevDID = currNode->did;
			}
			index++;
			subStr = " ";
			while (str[index] != ',') // Separate the AID from the str string
			{
				subStr += str[index];
				index++;
			}
			int aid = stoi(subStr);
			index++;
			subStr = " ";
			while (str[index] != ',') // Separate the album ABID from the str string
			{
				subStr += str[index];
				index++;
			}
			int abid = stoi(subStr);
			index++;
			subStr = "";
			while (str[index] != '\0') // Separate the year from the str string
			{
				subStr += str[index];
				index++;
			}
			Albums<T1>* newAlbum = new Albums<T1>; // Create a new album
			AD<T1, string, float>* temp = adHead;
			while (temp->abid != abid) // Find the album with the current ABID
				temp = temp->next;
			newAlbum->albumRef = temp;
			newAlbum->year = stoi(subStr); // The subStr string currently has the year
			newAlbum->next = NULL;
			if (currNode->albums == NULL) // No albums have been added in the current discography playlist
				currNode->albums = newAlbum; // Add the album at the every front of the albums pointer in the current discography
			else // Albums have been added previously in the current discography playlist
			{
				Albums<T1>* currAlbum = currNode->albums; 
				while (currAlbum->next != NULL) // Find the last album that was added for the current discography playlist
					currAlbum = currAlbum->next;
				currAlbum->next = newAlbum; // Add the current album after this last album
			}
			temp->adp = currNode; // Direct access from AMD class to current (ADP) class
			if (flag) // A new node was made above and must be added to the ADP list
			{
				// Two-way linking between the ADP and the AMD
				AMD<T1, string>* temp = amdHead;
				while (temp->aid != aid) // Find the album in the AMD linked list with the current AID
					temp = temp->next;
				temp->adp = currNode; 
				currNode->author = temp; // The author pointer points to the author's metadata in the AMD linked list
				if (adpHead == NULL) // The ADP linked list is currently empty
				{
					adpHead = currNode; // Add the current node at the very front of the ADP linked list
					currNode->next = NULL;
				}
				else // The ADP linked list is not currently empty 
				{
					prevNode->next = currNode; // Add current node after previous node
					currNode->next = NULL;
				}
				prevNode = currNode;
			}
		}
		currNode->next = adpHead; // Complete circular connecton
		iFile.close();
		return adpHead;
	}
	cout << "Error creating the Author Discography Playlist! The Discography.csv file could not be opened." << endl;
	return NULL;
}

template<typename T1, typename T2, typename T3>
MMD<T1, T2, T3>* Search_Music(int MBID)
{
	MMD<T1, T2, T3>* find = mmdHead;
	while (find->mbid != MBID) // Keep traversing the MMD list until the required MBID is found
	{
		if (find->next == NULL) // If the end of the linked list has been reached, return NULL
			return NULL;
		find = find->next; // Move to the next node
	}
	return find;
}

template<typename T1, typename T2>
AMD<T1, T2>* Search_Author(int AID)
{
	AMD<T1, T2>* find = amdHead;
	while (find->aid != AID) // Keep traversing the AMD linked list until the required AID is found
	{
		if (find->next == amdHead) // If the end of the linked list has been reached, return NULL
			return NULL;
		find = find->next; // Move to the next node
	}
	return find;
}

template<typename T1, typename T2, typename T3>
AD<T1, T2, T3>* Search_Album(int ABID)
{
	AD<T1, T2, T3>* find = adHead;
	while (find->abid != ABID) // Keep traversing the AD linked list until the required ABID is found
	{
		if (find->next == adHead) // If the end of the linked list has been reached, return NULL
			return NULL;
		find = find->next;
	}
	return find; // Move to the next node
}

template<typename T1>
ADP<T1>* Search_Discography(int DID)
{
	ADP<T1>* find = adpHead;
	while (find->did != DID) // Keep traversing the ADP linked list until the required DID is found
	{
		if (find->next == adpHead) // If the end of the linked list has been reached, return NULL
			return NULL;
		find = find->next; // Move to the next node
	}
	return find;
}

template <typename T1>
Tracks<T1>* Search_Music_By_Album(int ABID)
{
	AD<T1, string, float>* find = adHead; // Keep traversing the AD linked list until the node with the required ABID is found
	while (find->abid != ABID)
	{
		if (find->next == adHead) // If the end of the linked list has been reached, return NULL
			return NULL;
		find = find->next;
	}
	return find->tracks; // Return the tracks list of the node with the required ABID
}

template<typename T1>
Albums<T1>* Search_Music_By_Author(int DID)
{
	ADP<T1>* find = adpHead;
	while (find->did != DID) // Keep traversing the DID linked list until the node with the required DID is found
	{
		if (find->next == adpHead) // If the end of the linked list is reached, return NULL
			return NULL;
		find = find->next;
	}
	return find->albums; // Return the albums list of the node with the required DID
}