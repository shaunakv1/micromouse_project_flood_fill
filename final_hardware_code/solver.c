/**
 * @author Shaunak Vairagare
 *
 */
        
        //macro Definations 
        #define N 0
        #define E 1
        #define S 2
        #define W 3
        #define B 100
        
        //Logical Storage
        unsigned char mouseR;
        unsigned char mouseC;

        unsigned char ori;
        unsigned char quad;
        unsigned char zone;
        unsigned char pathcount;
        unsigned char deadFlag;
        unsigned char cameFrom;
        unsigned char map[33][33];
        unsigned char wall[4];
        unsigned char wallflood[]={

                        14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14,
                        13, 12, 11, 10,  9, 8, 7, 6, 6, 7, 8,  9, 10, 11, 12, 13,
                        12, 11, 10,  9,  8, 7, 6, 5, 5, 6, 7,  8,  9, 10, 11, 12,
                        11, 10,  9,  8,  7, 6, 5, 4, 4, 5, 6,  7,  8,  9, 10, 11,
                        10,  9,  8,  7,  6, 5, 4, 3, 3, 4, 5,  6,  7,  8,  9, 10,
                         9,  8,  7,  6,  5, 4, 3, 2, 2, 3, 4,  5,  6,  7,  8,  9,
                         8,  7,  6,  5,  4, 3, 2, 1, 1, 2, 3,  4,  5,  6,  7,  8,
                         7,  6,  5,  4,  3, 2, 1, 0, 0, 1, 2,  3,  4,  5,  6,  7,
                         7,  6,  5,  4,  3, 2, 1, 0, 0, 1, 2,  3,  4,  5,  6,  7,
                         8,  7,  6,  5,  4, 3, 2, 1, 1, 2, 3,  4,  5,  6,  7,  8,
                         9,  8,  7,  6,  5, 4, 3, 2, 2, 3, 4,  5,  6,  7,  8,  9,
                        10,  9,  8,  7,  6, 5, 4, 3, 3, 4, 5,  6,  7,  8,  9, 10,
                        11, 10,  9,  8,  7, 6, 5, 4, 4, 5, 6,  7,  8,  9, 10, 11,
                        12, 11, 10,  9,  8, 7, 6, 5, 5, 6, 7,  8,  9, 10, 11, 12,
                        13, 12, 11, 10,  9, 8, 7, 6, 6, 7, 8,  9, 10, 11, 12, 13,
                        14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14

                        };

        //Functions to replace in code finally
        unsigned char m(unsigned char val)//to convert mouse coordinates in to matrix coordinate
        {
                return (unsigned char)((val*2)+1);
        }
        unsigned char valInArray(unsigned char r,unsigned char c)
	{
		unsigned char val=0;
				
		val=(unsigned char)((r*16)+c);
		return val;
	}
        void initializeSystem()
        {
                unsigned char r;
                unsigned char c;
                 mouseR=15;
                 mouseC=0;
                 
                 ori=N;
                 quad=3;
                 zone=6;
                 pathcount=2;
                 deadFlag=FALSE;
                 cameFrom=S;
                 map[32][1]=1;
                 wall[N]=1;
                 
                 for(r=0;r<16;r++)
                         for(c=0;c<16;c++)
                         {
                                 map[m(r)][m(c)]=1;
                                
                         }
                
                 
                 
        }
        
        
        
       
        
        void move_north()
        {
               
                mouseR-=1;
                ori=N;
                if(deadFlag==FALSE)pathcount++;
                else  if(deadFlag==TRUE)pathcount--;
                
        }
        
        void move_south()
        {
                
                mouseR+=1;
                ori=S;

                if(deadFlag==FALSE)pathcount++;
                else if(deadFlag==TRUE) pathcount--;
        }

        void move_east()
        {
               
                mouseC+=1;
                ori=E;

                if(deadFlag==FALSE)pathcount++;
                else if(deadFlag==TRUE) pathcount--;
        }

        void move_west()
        {
                
                mouseC-=1;
                ori=W;
                
                if(deadFlag==FALSE)pathcount++;
                else if(deadFlag==TRUE) pathcount--;
                       
        }

        void setdead(unsigned char r, unsigned char c)
        {
                map[r][c]=0;
                deadFlag=TRUE;
        }
        
        void backtrack()
        {
               
                
                setdead(m(mouseR),m(mouseC));

                   if(cameFrom==S && wall[S]==FALSE) move_south();
         else if(cameFrom==W && wall[W]==FALSE) move_west();
         else if(cameFrom==N && wall[N]==FALSE) move_north();
         else if(cameFrom==E && wall[E]==FALSE) move_east();
                  
        }
        
        void see_where_you_came_from()
        {
            
                if(mouseR>0 &&  map[m(mouseR)-2][m(mouseC)  ]==(pathcount-1)) cameFrom=N;
         else if(mouseC<15 && map[m(mouseR)  ][m(mouseC)+2]==(pathcount-1)) cameFrom=E;
         else if(mouseR<15 && map[m(mouseR)+2][m(mouseC)  ]==(pathcount-1)) cameFrom=S;
         else if(mouseC>0 &&  map[m(mouseR)  ][m(mouseC)-2]==(pathcount-1)) cameFrom=W;
        }
        
        void scan()
        {
                char sensorOp,LL,FF,RR;
                sensorOp=readSensors();//this function returns 1's/0's in LFR format
                                
                LL=(ori-1);
                if(LL<0)LL=W;
                FF=ori;
                RR=(char)((ori+1)%4);//to keep o/p between NESW(0,1,2,3)
                        
                
                wall[(ori+2)%4]=wall[(((ori+2)%4)+2)%4];
                wall[RR]=(char)(sensorOp%10);sensorOp/=10;
                wall[FF]=(char)(sensorOp%10);sensorOp/=10;
                wall[LL]=(char)(sensorOp%10);
                              
        }
        
        
        
        unsigned char sense()//returns 1 when center reached
        {
               
                map[m(mouseR)][m(mouseC)]=pathcount;
                
                //if(deadFlag==FALSE)
                {        
                        scan();
                        map[m(mouseR)-1][m(mouseC)]=wall[N];
                        map[m(mouseR)][m(mouseC)+1]=wall[E];
                        map[m(mouseR)+1][m(mouseC)]=wall[S];
                        map[m(mouseR)][m(mouseC)-1]=wall[W];
                }
                
                deadFlag=FALSE;
                ////////////////////// Add Wall info in map matrix ////////////
                
                
                /////////////////////  mark new paths /////////////////////////
                
            if(mouseR >0  && wall[N]==FALSE && map[m(mouseR)-2][m(mouseC)]==1)  map[m(mouseR)-2][m(mouseC)]=255; 
            if(mouseR <15 && wall[S]==FALSE && map[m(mouseR)+2][m(mouseC)]==1)  map[m(mouseR)+2][m(mouseC)]=255;
            if(mouseC >0  && wall[W]==FALSE && map[m(mouseR)][m(mouseC)-2]==1)  map[m(mouseR)][m(mouseC)-2]=255;
            if(mouseC <15 && wall[E]==FALSE && map[m(mouseR)][m(mouseC)+2]==1)  map[m(mouseR)][m(mouseC)+2]=255;
                
            //////////// win condition///////////////////

                   /*if((map[m(mouseR)-2][m(mouseC)-2]>1)&&(map[m(mouseR)-2][m(mouseC)-1]==0)&&(map[m(mouseR)-2][m(mouseC)]>1)&&(map[m(mouseR)-1][m(mouseC)-2]==0)&&(map[m(mouseR)-1][m(mouseC)]==0)&&(map[m(mouseR)][m(mouseC)-2]>1)&&(map[m(mouseR)][m(mouseC)-1]==0)&&(map[m(mouseR)][m(mouseC)]>1))
                return(1);
                else
                if((map[m(mouseR)+2][m(mouseC)+2]>1)&&(map[m(mouseR)+2][m(mouseC)+1]==0)&&(map[m(mouseR)+2][m(mouseC)]>1)&&(map[m(mouseR)+1][m(mouseC)+2]==0)&&(map[m(mouseR)+1][m(mouseC)]==0)&&(map[m(mouseR)][m(mouseC)+2]>1)&&(map[m(mouseR)][m(mouseC)+1]==0)&&(map[m(mouseR)][m(mouseC)]>1))
                return(1);
                else return(0);*/
                
           if((mouseR==7&&mouseC==7)||(mouseR==7&&mouseC==8)||(mouseR==8&&mouseC==7)||(mouseR==8&&mouseC==8))
                 {
                  return(1);
                  }
           else
           return(0);

        }
        
        void moveByFloodPriority()
        {
                        
                unsigned char min=100;//just to check if min has  first value
                unsigned char selectDir=B;
                
                
                 if(mouseR >0  && wall[N]==FALSE && (map[m(mouseR)-2][m(mouseC)]>map[m(mouseR)][m(mouseC)]))
                 {
                        
                         if(min==100)min=wallflood[valInArray((unsigned char)(mouseR-1), mouseC)];
                         if(wallflood[valInArray((unsigned char)(mouseR-1), mouseC)]<=min)
                         {
                                 min=wallflood[valInArray((unsigned char)(mouseR-1), mouseC)];
                                 selectDir=N; 
                         }
                         
                         
                         
                 }
                if(mouseC <15 && wall[E]==FALSE && (map[m(mouseR)][m(mouseC)+2]>map[m(mouseR)][m(mouseC)]))
                {
                        
                        if(min==100)min=wallflood[valInArray(mouseR,(unsigned char) (mouseC+1))];
                        if(wallflood[valInArray(mouseR,(unsigned char) (mouseC+1))]<=min)
                        {
                                 min=wallflood[valInArray(mouseR,(unsigned char) (mouseC+1))];
                                 selectDir=E; 
                        }
                        
                        
                }
                if(mouseR <15 && wall[S]==FALSE && (map[m(mouseR)+2][m(mouseC)]>map[m(mouseR)][m(mouseC)])) 
                 {
                        
                        if(min==100)min=wallflood[valInArray((unsigned char)(mouseR+1), mouseC)]; 
                        if(wallflood[valInArray((unsigned char)(mouseR+1), mouseC)]<=min)
                         {
                                 min=wallflood[valInArray((unsigned char)(mouseR+1), mouseC)];
                                 selectDir=S;
                         }
                        
                        
                 }
                if(mouseC >0  && wall[W]==FALSE && (map[m(mouseR)][m(mouseC)-2]>map[m(mouseR)][m(mouseC)])) 
                 {
                        
                        if(min==100)min=wallflood[valInArray(mouseR,(unsigned char) (mouseC-1))]; 
                        if(wallflood[valInArray(mouseR,(unsigned char) (mouseC-1))]<=min)
                         {
                                 min=wallflood[valInArray(mouseR,(unsigned char) (mouseC-1))];
                                 selectDir=W;
                         }
                       
                         
                 }
                
                if(selectDir==N)move_north();
                else if(selectDir==E)move_east();
                else if(selectDir==S)move_south();
                else if(selectDir==W)move_west();
                else if(selectDir==B)backtrack();
        
                 see_where_you_came_from();
        }
    

         void solveMaze()
        {
                  unsigned char centerReached=FALSE;
                initializeSystem();
                while(centerReached==FALSE)
                {
                       
                        centerReached=sense();
                        
                        
                        moveByFloodPriority();
                       
                        
                       
                        
                }
                
        }
