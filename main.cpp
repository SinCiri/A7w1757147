#include <iostream>
#include <fstream>
#include <sstream>
#include<string>

#include "Queuecpp.h"
#include "Songcpp.h"
#include "RequestCpp.h"

void populateRequests(Queue<Request>& q);
void populateSongDataBase(LinkedList<Song> &list);
void processQueue(LinkedList<Song> &list,Queue<Request>& q);
void processRequest(LinkedList<Song>& list, std::string action, std::string title,std::string singer,int chartPos);

//GIVEN
int main() {
 
  LinkedList<Song> list;
  Queue<Request> q;

  populateSongDataBase(list); // fill the Songs Data Base into Linked List 
  
  std::cout<<"*************************************\n";
  list.printList(); // 
   std::cout<<"*************************************\n";
  populateRequests(q); // fill the request q
  std::cout<<"\n";
  std::cout<<"---------------PRINTING QUEUE-------------------\n";
   q.printList();
  std::cout<<"------------------------------------\n";
  processQueue(list,q); // process the requests
  std::cout<<"*************************************\n";
  list.printList();
 std::cout<<"*************************************\n";
 
} 
//GIVEN
//Requires  an empty linked list
//Effects fills the list with request by reading from the RequestData.txt
//Modifies the queue by filling it
void populateRequests(Queue<Request> &q){
  std::string line="";
  std::string token="";
  std::string title="";
  std::string singer="";
  std::string action="";
  int chartPos=-1;
 std::cout<<"*************** IN POPULATE REQUEST ***************\n";
  try {
  
    std::ifstream input("RequestData.txt");
    if (input.fail())
      throw new std::string("FILE OPEN ERROR EXCEPTION \n");
    else{
      while (getline(input,line)){
        std::istringstream instream(line);
       
         //std::cout<<line <<"\n";
          getline(instream,action,',');
          getline(instream,title,',');
          getline(instream,singer,',');
          instream>>chartPos;
        // create a Request object 
          Request r(action,title,singer,chartPos);
         // std::cout<<r.getAction()<<"\n";
         // add it to the queue..
          q.add(r);
         
        }

      }
  
    }

  
  
  catch(std::string message){
    std::cout<<message;
    exit(-1);
  }

}

//GIVEN
//Requires Filled data base , song to play
//Effects Finds song using get, if found plays it
//Modifies nothing
 std::string playSong(LinkedList<Song>&list, Song s){
   
  
   if (list.get(s)>=0){
    
      return "PLAYING :"+ s.toString()+"\n";
   }
    else{
      return "SONG NOT FOUND\n";
      
    }
 
 }

//GIVEN
//Requires filled database
//Effects calls print methood to print top ten songs
//Modifies nothing
void printTopTenSongs(LinkedList<Song>& list){
    std::cout<<"PLAYING TOP TEN SONG __________\n";
  list.print(10);
}

//Requires filled Song Database, a Song to add. The chart position given in the song is where it will get added. Note this is a Song that is not supposed to exist in database. 
//Effects adds the song from its original chart position 
//Modifies the Song database. Adjust chart position of all Songs affected by this addition- this adjustment is done in insert method using adjustPosition method. If the Process Queue adds a Song that already is in the database, then a duplicate entry can occur.
//TODO
void addThisSong(LinkedList<Song> &list, Song s){
 //TODO
  int chartPos = s.getChartPosition();
  //to allow song to display when printSong is called
  if (chartPos>list.size()) {
    std::cout << list.size() << std::endl;
    chartPos = list.size();
  }
 
  if (chartPos>=0) {
    list.insert(s, chartPos);

    std::cout<<"ADDED THIS SONG "<<chartPos<<" " ;
    list.printSong(chartPos); 
    std::cout << "\n";
    }
  else std::cout<<"SORRY CANNOT FIND SONG \n";
  
  
 
}

//TODO
//Requires filled Song Database, a Song to remove 
//Effects if found, removes the song from its original chart position 
//Modifies the Song database. Adjust chart position of all Songs affected by this removal- this adjustment is done in remove method using adjustPosition method
void removeThisSong(LinkedList<Song> &list, Song s){

  int found = list.get(s);

  if (found<0) {
    std::cout<<"SORRY CANNOT REMOVE THIS SONG - SONG NOT FOUND "<< "\n";
    }
  else{ 
        int chartPos = s.getChartPosition();
        list.remove(s);
        std::cout<<"REMOVED THIS SONG \n"; 
        std::cout<<"THE SONG AT CHARTPOSITION "<<chartPos<<" IS NOW ";
        list.printSong(chartPos); std::cout<<"\n";
        
       return;
 
  }
}


//TODO
//Requires filled Song Database, a Song to move and its new position
//Effects removes the song from its original chart position and inserts into given position
//Modifies the Song database. Adjust chart position of all Songs affected by this insertion and removal. - this adjustment is done in remove method using adjustPosition method
void moveThisSong(LinkedList<Song> &list, Song s, int pos) {
  int chartPos=list.get(s);
 
  std::cout<<"MOVING SONG "<<s.toString()<<"\n";
   list.move(s,pos);
   std::cout<<"ITS NEW CHART POSITION  \n";
   list.printSong(pos);
   std::cout<<"THE SONG AT PREVIOUS POSITION "<<chartPos+1<< " IS NOW ";list.printSong(chartPos+1);
   
}
 //GIVEN
  //Requires filled database, a single request 
  //Effects Processes the request 
  //Modifies nothing
 
 void processRequest(LinkedList<Song> &list,std::string action, std::string title,std::string singer,int chartPos){
 
   Song s(title,singer,chartPos);
   char ch =action[0];
   

    switch(ch){
      case 'P' : std::cout<<playSong(list,s)<<"\n";break;
      case 'A' : addThisSong(list,s);break;;
      case 'R' : removeThisSong(list,s);break;
      case 'M' : moveThisSong(list,s,chartPos);break;
      case 'T' : printTopTenSongs(list);break;
    }
  }

//TODO
  //Requires filled database, filled Request Queue
  //Effects Processes requests by implementing the action given in each request
  //Modifies q, empties it after processing
 
void processQueue(LinkedList<Song> &list ,Queue<Request>& q){
   
   int requestNumber=1;
   //Create an iterator for the Queue to iteratate through requests
        Queue<Request>::Iterator iter(q.begin());
       std::cout<<"-------------------------------------------------------------------------\n";
         // call processRequest
         //processRequest(iter.getCur()->getData().getAction(), );
        int requestNum = 0;
         while(iter.getCur()) {
            requestNum++;
            std::string action = iter.getCur()->getData().getAction();
            std::string singer = iter.getCur()->getData().getSinger();
            std::string title = iter.getCur()->getData().getTitle();
            int chartPos = iter.getCur()->getData().getChartPosition();
            std::cout << "Request Number "<< requestNum << " " << iter.getCur()->toString() << std::endl;
            processRequest(list, action, title, singer, chartPos);
            iter = iter.next();
            std::cout<<"-------------------------------------------------------------------------\n";
     
           std::cout<<"-------------------------------------------------------------------------\n";
         }
        
}

//GIVEN
//Requires the empty linked list database
//Effects if the file exists and accessible, reads from file and inserts songs 
// IN SORTED ORDER  ACCORDING TO CHART POSITION// Big O(N^2)  ---> Why?
//Modifies list - fills it with songs, returns sorted linked list
void populateSongDataBase(LinkedList<Song> &list){
  std::string line="";
 std::string token="";
  std::string title="";
  std::string singer="";
  int chartPos=-1;
   try {
    std::ifstream input("SongsData.txt");
    if (input.fail())
      throw new std::string("FILE OPEN ERROR EXCEPTION \n");
    else{
      while (getline(input,line)){
        std::istringstream instream(line);
          getline(instream,title,',');
          getline(instream,singer,',');
          instream>>chartPos;
          Song s(title,singer,chartPos);
          list.insert(s);
        }

}
   
   }
   catch(std::string message){
     std::cout<<message;
   }

}