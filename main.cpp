#include <iostream>
#include <stdlib.h>//for clear screen
#include <vector>//for multiple player
#include <fstream>//store value in a file
#include <string>//for multiple words
#include<bits/stdc++.h>//for vector to transfer to functions

using namespace std;
struct Player//for multiple player variable
{
    string name;
    string ID;
    string age;
};

//Function Protoypes
int EasyLevel();//Modulated Easy Level Questionnaire and Score
int NormalLevel();//Modulated Normal Level Questionnaire and Score
int HardLevel();//Modulated Hard Level Questionnaire and Score
void Addplayer(int Count,vector<Player>& players);//function that adds player
int Find(int Count, vector<Player>& players);//find similar id number
void sorter(float Arr[],int arr_size,int indexes[]);//Sorts score for rankings
void toFile(float arrvalue[],int arrindex[],int number,vector<Player> players);//manipulate data file for overall score
void toFilePer(float arrvalue[],int arrindex[],int number,vector<Player> players);//manipulate data file for  score percentage
void toRank(float arrvalue[],int arrindex[],int number,vector<Player> players);//for ranking
void toRankPer(float arrvalue[],int arrindex[],int number,vector<Player> players);//for ranking

int main()
{
    //LOCAL DECLARATION OF PLAYER RELATED VARIABLES
    vector<Player> players(100);
    int Playerloop=1;
    float scoreoverall[100];
    float scorepercent[100];
    int nameindex[100];
    int invalid;
    string play;



    do//LOOPS IF USER ENTERED CHARACTER NOT IN THE  CHOICES
    {
        cout << "\n\t----------MATH QUIZ GAME----------"<<endl;
        cout << "\n   MAIN MENU"<<endl;
        cout << "\n\t Play - P\n\t Ranking - R\n\t Save - S\n\t Exit - E"<<endl;//first condition
        cout <<"\n\t:";
        cin >> play;
        system("cls");

        if((play=="P"||play=="p") || play=="Play")//IF USER PLAYS
        {
            do
            {
                Addplayer(Playerloop,players);//access the function
                if(Playerloop==1)
                {
                    break;
                }
                invalid=Find(Playerloop,players);
                if(invalid==1)
                {
                    cout <<"Player already exists."<<endl;
                }
                else
                {
                    break;
                }
            }while(invalid==1);
            system("cls");//CLEAR SCREEN
            //INSTRUCTIONS
            cout << "\n\t----------MATH QUIZ GAME----------"<<endl;
            cout << "Instructions:"<<endl;
            cout << "\n > Answer in Lowercase Letters ONLY!"<<endl;
            cout << "\n > Hit enter key after you answer a question."<<endl;
            cout << "\n > Answer should be in the choices, if not, marked as incorrect."<<endl;
            cout << "\n(Click ENTER key to proceed)"<<endl;
            cin.ignore();//REMOVE CIN VALUE FROM PREVIOUS BLOCK OF CODE
            cin.get();//ACCEPTS ENTER KEY

            //LOCAL DECLARATION OF VARIABLES
            int loop=0;
            float Percent=0,correctScore=0;
            string category;
            string again;
                  do{//IF USER WANTS TO PLAY ANOTHER LEVEL
                        int Easy=0,Normal=0,Hard=0,Total=0,overall=0,Allmistakes=0;
                        system("cls");

                        do//LOOP FOR INVALID CATEGORY THE USER ENTERED
                        {
                            //CATEGORY SELECTION
                            cout <<"\n1 - Easy\n2 - Normal\n3 - Hard\n";
                            cout <<"\nEnter Difficulty Level: ";
                            cin >>category;

                            system("cls");

                            if(category=="1")//ENTER EASY LEVEL
                            {

                                Easy=EasyLevel();//ACCESS FUNCTION
                            }//if

                            else if(category=="2")//ENTER NORMAL LEVEL
                            {

                                Normal=NormalLevel();//ACCESS FUNCTION
                            }

                            else if(category=="3")//ENTER HARD LEVEL
                            {

                                Hard=HardLevel();//ACCESS FUNCTION
                            }//else if

                            else//NOT IN THE OPTION
                            {
                                cout << "\nInvalid Category\n"<<endl;
                            }

                            if(category=="1"||category=="2"||category=="3")//DISPLAY RESULTS AFTER EACH ITEM
                            {
                                //CALCULATE PLAYER STATISTICS
                                loop++;
                                overall=10*loop;
                                Total=Easy+Normal+Hard;
                                correctScore=Total+correctScore;
                                Allmistakes=overall-correctScore;
                                Percent=(correctScore/(10*loop))*100;
                                cout <<"Total Correct Items: "<<correctScore<<endl;
                                cout << "Total Mistaken Items: "<<Allmistakes<<endl;
                                cout<<"Total Items:"<<correctScore<<"/"<<overall<<endl;;
                                cout <<"Correct Rate: "<<Percent<<"%"<<endl;

                                //STORE VALUE IN AN ARRAY
                                scoreoverall[Playerloop-1]=correctScore;
                                scorepercent[Playerloop-1]=Percent;
                            }

                        }while(category!="1"&&category!="2"&&category!="3");


                        do//LOOPS IF THE USER ENTERED NEITHER YES OR NO
                        {
                            cout << "\nWould you like to play another level ?(Y/N)"<<endl;
                            cin >> again;
                            system("cls");
                            if(again=="N"||again=="n")//EXIT GAME LEVEL
                            {
                                cout <<"Returning to Main Menu."<<endl;
                                cout <<"Player Logging Out."<<endl;
                                break;
                            }
                            else if(again=="Y"||again=="y")//PLAYS ANOTHER LEVEL
                            {
                                break;//TERMINATE LOOP
                            }
                            else//DETERMINE IF THE USERS INPUT IS INVALID
                            {
                                cout <<"Invalid Option."<<endl;
                            }
                        }while(true);

                    }while(again=="y"||again=="Y");
            Playerloop++;
        }
        else if((play=="R"||play=="r")||play=="Ranking" )//IF WANTS TO KNOW THEIR RANK
        {
            sorter(scoreoverall,Playerloop,nameindex);
            toFile(scoreoverall,nameindex,Playerloop,players);
            sorter(scorepercent,Playerloop,nameindex);
            toFilePer(scorepercent,nameindex,Playerloop,players);

            string again;
            cout << "\nPress ENTER key to return.";
            cin.ignore();
            cin.get();
            system("cls");
            cout <<"Returning to Main Menu."<<endl;

        }
        else if((play=="S"||play=="s")||play=="Save" )//IF WANTS TO KNOW THEIR RANK
        {
            cout <<"Saving to File..."<<endl;
            sorter(scoreoverall,Playerloop,nameindex);
            toFile(scoreoverall,nameindex,Playerloop,players);
            sorter(scorepercent,Playerloop,nameindex);
            toFilePer(scorepercent,nameindex,Playerloop,players);

            cout <<"\nSaved to File Finale."<<endl;
            string again;
            cout << "\nPress ENTER key to return.";
            cin.ignore();
            cin.get();
            system("cls");
            cout <<"Returning to Main Menu."<<endl;



        }
        else if((play=="E"||play=="e") ||play=="Exit")//IF USER WON'T PLAY
        {
            cout <<"Exiting Game..."<<endl;
            break;
        }
        else//IF NOT  YES OR NO
        {
            cout << "\nInvalid Option\n"<<endl;
        }
    }while(true);
    return 0;
}

int EasyLevel()
{
    int scoreEasy=0;
    for(int i=1;i<=10;i++)//to display score after each number
    {
        cout <<" BEGINNER"<<endl;
        char answer;
        if(i==1)//Easy Question no.1
        {
            cout << "1.) Multiply:\t8 x 84"<<endl;
            cout << "\ta. 96"<<endl;
            cout << "\tb. 762"<<endl;
            cout << "\tc. 238"<<endl;
            cout << "\td. 672"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

                if(answer=='d'||answer=='D')//DETERMINES CORRECT ANSWER
                {
                    cout <<" \nCORRECT!\n"<<endl;;
                    scoreEasy++;
                }
                else
                {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: d\n"<<endl;
                }
        }

        else if(i==2)//Easy Question no.2
        {
            cout << "2.) Multiply:\t5 x 9"<<endl;
            cout << "\ta. 14"<<endl;
            cout << "\tb. 4"<<endl;
            cout << "\tc. 45"<<endl;
            cout << "\td. 0"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='c'||answer=='C')
            {
                cout <<"\nCORRECT!"<<endl;;
                scoreEasy++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: c\n"<<endl;
            }
        }

        else if(i==3)//Easy Question no.3
        {
            cout << "3.) Multiply:\t20 x 27"<<endl;
            cout << "\ta. 1540"<<endl;
            cout << "\tb. 540"<<endl;
            cout << "\tc. 5040"<<endl;
            cout << "\td. 777"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='b'||answer=='B')
            {
                cout <<"\nCORRECT!"<<endl;;
                scoreEasy++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: b\n"<<endl;
            }
        }

        else if(i==4)//Easy Question no.4
        {
            cout << "4.) Divide:\t75/25"<<endl;
            cout << "\ta. 3"<<endl;
            cout << "\tb. 2"<<endl;
            cout << "\tc. 4"<<endl;
            cout << "\td. 5"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='a'||answer=='A')
            {
                cout <<"\nCORRECT!"<<endl;;
                scoreEasy++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: a\n"<<endl;
            }
        }

        else if(i==5)//Easy Question no.5
        {
            cout << "5.) Subtract:\t528-173"<<endl;
            cout << "\ta. 355"<<endl;
            cout << "\tb. 455"<<endl;
            cout << "\tc. 619"<<endl;
            cout << "\td. 247"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='a'||answer=='A')
            {
                cout <<"\nCORRECT!"<<endl;;
                scoreEasy++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: a\n"<<endl;
            }
        }

        else if(i==6)//Easy Question no.6
        {
            cout << "6.) What is -17-3"<<endl;
            cout << "\ta. -20"<<endl;
            cout << "\tb. -14"<<endl;
            cout << "\tc. 14"<<endl;
            cout << "\td. 20"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='a'||answer=='A')
            {
                cout <<"\nCORRECT!"<<endl;;
                scoreEasy++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: a\n"<<endl;
            }
        }

        else if(i==7)//Easy Question no.7
        {
            cout << "7.) Which expression represents two more than five times a number n?"<<endl;
            cout << "\ta. 7n"<<endl;
            cout << "\tb. 5n+2"<<endl;
            cout << "\tc. (2+5)n"<<endl;
            cout << "\td. 2(5n)"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='b'||answer=='B')
            {
                cout <<"\nCORRECT!"<<endl;;
                scoreEasy++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: b\n"<<endl;
            }
        }

        else if(i==8)//Easy Question no.8
        {
            cout << "8.) Express as an integer: at sea level"<<endl;
            cout << "\ta. 0"<<endl;
            cout << "\tb. -0"<<endl;
            cout << "\tc. 1"<<endl;
            cout << "\td. -10"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='a'||answer=='A')
            {
                cout <<"\nCORRECT!"<<endl;;
                scoreEasy++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: a\n"<<endl;
            }
        }

        else if(i==9)//Easy Question no.9
        {
            cout << "9.) What is -9-6 is equal to?"<<endl;
            cout << "\ta. -15"<<endl;
            cout << "\tb. -3"<<endl;
            cout << "\tc. 3"<<endl;
            cout << "\td. 15"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='a'||answer=='A')
            {
                cout <<"\nCORRECT!"<<endl;;
                scoreEasy++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: d\n"<<endl;
            }
        }

        else if(i==10)//Easy Question no.10
        {
            cout << "10.) What is 582 x 100?"<<endl;
            cout << "\ta. 58220"<<endl;
            cout << "\tb. 5822"<<endl;
            cout << "\tc. 55800"<<endl;
            cout << "\td. 58200"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='d'||answer=='D')
            {
                cout <<"\nCORRECT!"<<endl;;
                scoreEasy++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: d\n"<<endl;
            }
            cout << "\n(Enter ENTER key to proceed)"<<endl;
            cin.ignore();
            cin.get();
            system("cls");
            //Display mistakes after the last item in the category
            int mistake;
            mistake=10-scoreEasy;
            cout<<"Number of Mistakes: "<<mistake<<"/10"<<endl;
        }

        cout <<"Score : "<<scoreEasy<<"/10"<<endl;

        cout << "\n(Click ENTER key to proceed)"<<endl;
        cin.ignore();
        cin.get();
        system("cls");


    }
    return scoreEasy;
}

int NormalLevel()
{
    int scoreNormal=0;
    for(int i=1;i<=10;i++)
    {
        char answer;
        cout <<" NORMAL"<<endl;

        if(i==1)//Normal Question no.1
        {
            cout << "1.) Which of the following is an obtuse angle?"<<endl;
            cout << "\ta. 134 Degree"<<endl;
            cout << "\tb. 89 Degree"<<endl;
            cout << "\tc. 189 Degree"<<endl;
            cout << "\td. 30 Degree"<<endl;
            cout << "\n\n Answer: ";

            cin >> answer;

            if(answer=='a'||answer=='A')
            {
                cout <<" \nCORRECT!\n"<<endl;;
                scoreNormal++;

            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: a\n"<<endl;
            }
        }

        else if(i==2)//Normal Question no.2
        {
            cout << "2.) How many odd number in the 1-100?"<<endl;
            cout << "\ta. 49"<<endl;
            cout << "\tb. 50"<<endl;
            cout << "\tc. 51"<<endl;
            cout << "\td. 52"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='b'||answer=='B')
            {
                cout <<" \nCORRECT!\n"<<endl;;
                scoreNormal++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: b\n"<<endl;
            }
        }

        else if(i==3)//Normal Question no.3
        {
            cout << "3.) What is the location in the given (0,0)."<<endl;
            cout << "\ta. none"<<endl;
            cout << "\tb. zero"<<endl;
            cout << "\tc. origin"<<endl;
            cout << "\td. positive"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='c'||answer=='C')
            {
                cout <<" \nCORRECT!\n"<<endl;;
                scoreNormal++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: c\n"<<endl;
            }
        }

        else if(i==4)//Normal Question no.4
        {
            cout << "4.) Find the median of the following numbers:\n\t1,3,5,7,9,11,13"<<endl;
            cout << "\ta. 13"<<endl;
            cout << "\tb. 7"<<endl;
            cout << "\tc. 5"<<endl;
            cout << "\td. 9"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='b'||answer=='B')
            {
                cout <<" \nCORRECT!\n"<<endl;;
                scoreNormal++;

            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: b\n"<<endl;
            }
        }

        else if(i==5)//Normal Question no.5
        {
            cout << "5.) What is the median of the following set?\n\t2,4,6,8,10,12,14,16"<<endl;
            cout << "\ta. 11"<<endl;
            cout << "\tb. 9"<<endl;
            cout << "\tc. 13"<<endl;
            cout << "\td. 7"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='b'||answer=='B')
            {
                cout <<" \nCORRECT!\n"<<endl;;
                scoreNormal++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: b\n"<<endl;
            }
        }

        else if(i==6)//Normal Question no.6
        {
            cout << "6.) What is the greatest common factor of 22 and 55?"<<endl;
            cout << "\ta. 11"<<endl;
            cout << "\tb. 50"<<endl;
            cout << "\tc. 85"<<endl;
            cout << "\td. 90"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='a'||answer=='A')
            {
                cout <<" \nCORRECT!\n"<<endl;;
                scoreNormal++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: a\n"<<endl;
            }
        }

        else if(i==7)//Normal Question no.7
        {
            cout << "7.) It is the comparison of two quantities."<<endl;
            cout << "\ta. decimal"<<endl;
            cout << "\tb. whole number"<<endl;
            cout << "\tc. integer"<<endl;
            cout << "\td. ratio "<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='d'||answer=='D')
            {
                cout <<" \nCORRECT!\n"<<endl;;
                scoreNormal++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: d\n"<<endl;
            }
        }

        else if(i==8)//Normal Question no.8
        {
            cout << "8.) How many centimeters are there in a meter?"<<endl;
            cout << "\ta. 100"<<endl;
            cout << "\tb. 2.54"<<endl;
            cout << "\tc. 550"<<endl;
            cout << "\td. 50 "<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='a'||answer=='A')
            {
                cout <<" \nCORRECT!\n"<<endl;;
                scoreNormal++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: a\n"<<endl;
            }
        }

        else if(i==9)//Normal Question no.9
        {
            cout << "9.) Give me the place value of 7 in 0.827"<<endl;
            cout << "\ta. millionths"<<endl;
            cout << "\tb. tenths"<<endl;
            cout << "\tc. hundreds"<<endl;
            cout << "\td. thousands"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='d'||answer=='D')
            {
                cout <<" \nCORRECT!\n"<<endl;;
                scoreNormal++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: d\n"<<endl;
            }
        }

        else if(i==10)//Normal Question no.10
        {
            cout << "10.) Measurement of a side of a square is 6m. Perimeter of a square is"<<endl;
            cout << "\ta. 36"<<endl;
            cout << "\tb. 12"<<endl;
            cout << "\tc. 24"<<endl;
            cout << "\td. 18 "<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='c'||answer=='C')
            {
                cout <<" \nCORRECT!\n"<<endl;;
                scoreNormal++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: c\n"<<endl;
            }
            cout << "\n(Click ENTER key to proceed)"<<endl;
            cin.ignore();
            cin.get();
            system("cls");
            //Display mistakes after the last item in the category
            int mistakes;
            mistakes=10-scoreNormal;
            cout<<"\nMistakes: "<<mistakes<<"/10"<<endl;
        }

        cout <<"Score : "<<scoreNormal<<"/10"<<endl;

        cout << "\n(Click ENTER key to proceed)"<<endl;
        cin.ignore();
        cin.get();
        system("cls");
    }
    return scoreNormal;
}

int HardLevel()
{
    int scoreHard=0;
    for(int i=1;i<=10;i++)
    {
        cout <<" HARD"<<endl;
        char answer;
        if(i==1)//Hard Question no.1
        {
            cout << "1.) Tom has e crayons, and Tim has y pencils. "<<endl;
            cout <<"Write an equation for the number of art(s) they have together."<<endl;
            cout << "\ta. e+y=s"<<endl;//degree command: hold alt keypad: 0176
            cout << "\tb. e*y=s"<<endl;//� = hold alt: 164(keypad)
            cout << "\tc. x+e=y"<<endl;
            cout << "\td. None of the Above"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='a'||answer=='A')
            {
                cout <<" \nCORRECT!\n"<<endl;;
                scoreHard++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: a\n"<<endl;
            }
        }

        else if(i==2)//Hard Question no.2
        {
            cout << "2.) Your mom is in the market. She bought 22 kg of fish and 24 kg of chicken. "<<endl;
            cout << "You ate 4 kg of chicken and 12 kg of fish. How many kg was left of the 2 foods combined? "<<endl;
            cout << "\ta. 34 kg"<<endl;
            cout << "\tb. 37 kg"<<endl;
            cout << "\tc. 41 kg"<<endl;
            cout << "\td. 30 kg"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='d'||answer=='D')
            {
                cout <<" \nCORRECT!\n"<<endl;;
                scoreHard++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: d\n"<<endl;
            }
        }

        else if(i==3)//Hard Question no.3
        {
            cout << "3.) What if you divide 352 by 12?"<<endl;
            cout << "\ta. 23.9"<<endl;
            cout << "\tb. 27.9"<<endl;
            cout << "\tc. 29.3"<<endl;
            cout << "\td. 67.8"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='c'||answer=='C')
            {
                cout <<" \nCORRECT!\n"<<endl;;
                scoreHard++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: c\n"<<endl;
            }
        }

        else if(i==4)//Hard Question no.4
        {
            cout << "4.) What if you multiply 45.5 by 2?"<<endl;
            cout << "\ta. 91"<<endl;
            cout << "\tb. 92"<<endl;
            cout << "\tc. 93"<<endl;
            cout << "\td. 90.5"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='a'||answer=='A')
            {
                cout <<" \nCORRECT!\n"<<endl;;
                scoreHard++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: b\n"<<endl;
            }
        }

        else if(i==5)//Hard Question no.5
        {
            cout << "5.) What if you add 7778.1 into 0.0001"<<endl;
            cout << "\ta. 7778.0010"<<endl;
            cout << "\tb. 7778.1001"<<endl;
            cout << "\tc. 7778.0011"<<endl;
            cout << "\td. 7779"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='b'||answer=='B')
            {
                cout <<" \nCORRECT!\n"<<endl;;
                scoreHard++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: b\n"<<endl;
            }
        }

        else if(i==6)//Hard Question no.6
        {
            cout << "6.) Which of the words has something to do with circles?"<<endl;
            cout << "\ta. fi"<<endl;
            cout << "\tb. perimeter"<<endl;
            cout << "\tc. pie"<<endl;
            cout << "\td. pi"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='d'||answer=='D')
            {
                cout <<" \nCORRECT!\n"<<endl;;
                scoreHard++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: d\n"<<endl;
            }
        }

        else if(i==7)//Hard Question no.7
        {
            cout << "7.) If it's 10:15 now, and the bus arrives at 11:10."<<endl;
            cout << " How many minutes do you have to wait for the bus?"<<endl;
            cout << "\ta. 55 minutes"<<endl;
            cout << "\tb. 45 minutes"<<endl;
            cout << "\tc. 35 minutes"<<endl;
            cout << "\td. just get the train instead. "<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='a'||answer=='A')
            {
                cout <<" \nCORRECT!\n"<<endl;
                scoreHard++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: a\n"<<endl;
            }
        }

        else if(i==8)//Hard Question no.8
        {
            cout << "8.) Which number is closest to 1200?"<<endl;
            cout << "\ta. 1066"<<endl;
            cout << "\tb. 1301"<<endl;
            cout << "\tc. 1145"<<endl;
            cout << "\td. 1260 "<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='c'||answer=='C')
            {
                cout <<" \nCORRECT!\n"<<endl;;
                scoreHard++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: c\n"<<endl;
            }
        }

        else if(i==9)//Hard Question no.9
        {
            cout << "9.) How many minutes are in half of a day?"<<endl;
            cout << "\ta. 720"<<endl;
            cout << "\tb. 640"<<endl;
            cout << "\tc. 6000"<<endl;
            cout << "\td. 240"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='a'||answer=='A')
            {
                cout <<" \nCORRECT!\n"<<endl;;
                scoreHard++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: a\n"<<endl;
            }
        }

        else if(i==10)//Hard Question no.10
        {
            cout << "10.) Anna's uncle have a rectangular sunflower field that "<<endl;
            cout << "measure 50 meters in length and 14 meters in width. What is it's area?"<<endl;
            cout << "\ta. 700 square meter"<<endl;
            cout << "\tb. 800 square meter"<<endl;
            cout << "\tc. 900 square meter"<<endl;
            cout << "\td. 600 square meter"<<endl;
            cout << "\n\n Answer: ";
            cin >> answer;

            if(answer=='a'||answer=='A')
            {
                cout <<" \nCORRECT!\n"<<endl;;
                scoreHard++;
            }
            else
            {
                cout <<"\nINCORRECT :("<<endl;
                cout <<"Correct Answer: c\n"<<endl;
            }
            cout << "\n(Click ENTER key to proceed)"<<endl;
            cin.ignore();
            cin.get();
            system("cls");
            //Display mistakes after the last item in the category
            int mistakes;
            mistakes=10-scoreHard;
            cout<<"\nMistakes: "<<mistakes<<"/10"<<endl;
        }

        cout <<"Score : "<<scoreHard<<"/10"<<endl;
        cout << "\n(Click ENTER key to proceed)"<<endl;
        cin.ignore();
        cin.get();
        system("cls");
    }//for
    return scoreHard;
}

void Addplayer(int Count,vector<Player>& players)
{
    //vector<Player> players(100);
    cout <<"Player "<<Count<<endl;
    cout <<"\tName: ";
    cin.ignore();
    getline(cin,players[Count-1].name);
    cout <<"\tAge: ";
    cin >>players[Count-1].age;
    cout <<"\tID: ";
    cin>>players[Count-1].ID;
}
int Find(int Count, vector<Player>& players)
{

    for(int i=0;i<Count-1;i++)
    {
        for(int j=i+1;j<Count;j++)
        {
            if(players[i].ID==players[j].ID)
            {
                return 1;
            }
        }
    }
    return 0;
}
void sorter(float Arr[],int arr_size,int indexes[])
{
    int val=arr_size-1;
    int Max,Maxidx,temp;
    int Index;
    for(int ii=0;ii<val;ii++)
    {
        indexes[ii]=ii;
    }
    for(int i=0;i<(val-1);i++)
    {
        Max=Arr[i];
        Maxidx=i;
        for(int j=i;j<val;j++)
        {
            if(Arr[j]>Max)
            {
                Max = Arr[j];
                Maxidx=j;
            }
        }
        if(Max>Arr[i])
        {
            temp=Arr[i];
            Arr[i]=Max;
            Arr[Maxidx]=temp;
            indexes[i]=Maxidx;

            Index=indexes[Maxidx];
            indexes[Maxidx]=indexes[i];
            indexes[i]=Index;
        }
    }
}
void toFile(float arrvalue[],int arrindex[],int number,vector<Player> players)
{

    ofstream outfile;
    outfile.open("Finale");
    outfile <<"\nOverall Score Rankings\n "<<"\nRank\tName\t\tScore"<<endl;
    for(int i=0;i<(number-1);i++)
    {
        outfile<<i+1<<"\t"<<players[arrindex[i]].name<<"\t\t"<<arrvalue[i]<<endl;
    }
    cout <<endl;
    outfile.close();

    ifstream infile;
    infile.open("Finale.txt");
    cout <<"From File:"<<endl;
    cout <<"\nOverall Score Rankings\n "<<"\nRank\tName\t\tScore"<<endl;

    for(int i=0;i<(number-1);i++)
    {
        infile>>arrindex[i];
        infile>>players[arrindex[i]].name;
        infile>>arrvalue[i];
        cout<<i+1<<"\t"<<players[arrindex[i]].name<<"\t\t"<<arrvalue[i]<<endl;
    }

}
void toFilePer(float arrvalue[],int arrindex[],int number,vector<Player> players)
{

    fstream outfile;
    outfile.open("Finale",ios::app);
    outfile <<"Score Percentage Rankings\n "<<"\nRank\tName\t\tScore"<<endl;
    for(int i=0;i<(number-1);i++)
    {
        outfile<<i+1<<"\t"<<players[arrindex[i]].name<<"\t\t"<<arrvalue[i]<<"%"<<endl;
    }
    outfile.close();

    ifstream infile;
    infile.open("Finale.txt");
    cout <<"\nScore Percentage Rankings\n "<<"\nRank\tName\t\tScore"<<endl;
    for(int i=0;i<(number-1);i++)
    {
        infile>>arrindex[i];
        infile>>players[arrindex[i]].name;
        infile>>arrvalue[i];
        cout<<i+1<<"\t"<<players[arrindex[i]].name<<"\t\t"<<arrvalue[i]<<"%"<<endl;
    }
    infile.close();
}
void toRank(float arrvalue[],int arrindex[],int number,vector<Player> players)
{

    ofstream outfile;
    outfile.open("Finale");
    outfile <<"\nOverall Score Rankings\n "<<"\nRank\tName\t\tScore"<<endl;
    for(int i=0;i<(number-1);i++)
    {
        outfile<<i+1<<"\t"<<players[arrindex[i]].name<<"\t\t"<<arrvalue[i]<<endl;
    }
    cout <<endl;
    outfile.close();

    ifstream infile;
    infile.open("Finale.txt");
    cout <<"\nOverall Score Rankings\n "<<"\nRank\tName\t\tScore"<<endl;

    for(int i=0;i<(number-1);i++)
    {
        infile>>arrindex[i];
        infile>>players[arrindex[i]].name;
        infile>>arrvalue[i];
        cout<<i+1<<"\t"<<players[arrindex[i]].name<<"\t\t"<<arrvalue[i]<<endl;
    }

}
void toRankPer(float arrvalue[],int arrindex[],int number,vector<Player> players)
{

    fstream outfile;
    outfile.open("Finale",ios::app);
    outfile <<"Score Percentage Rankings\n "<<"\nRank\tName\t\tScore"<<endl;
    for(int i=0;i<(number-1);i++)
    {
        outfile<<i+1<<"\t"<<players[arrindex[i]].name<<"\t\t"<<arrvalue[i]<<"%"<<endl;
    }
    outfile.close();

    ifstream infile;
    infile.open("Finale.txt");
    cout <<"\nScore Percentage Rankings\n "<<"\nRank\tName\t\tScore"<<endl;
    for(int i=0;i<(number-1);i++)
    {
        infile>>arrindex[i];
        infile>>players[arrindex[i]].name;
        infile>>arrvalue[i];
        cout<<i+1<<"\t"<<players[arrindex[i]].name<<"\t\t"<<arrvalue[i]<<"%"<<endl;
    }
    infile.close();
}
