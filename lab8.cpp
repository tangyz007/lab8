#include <iostream>
#include <cstring>

using namespace std;
#define MAX 100
#define number 26

 char Letters[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	 string morsecode[] ={ ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." };
	

class Message { 
	private: 
	// neither derived classes nor other users
	// can access private members
	protected:	
		//string msg;
		char* input;
		//int length;
	public:
		virtual void print(void);
		Message();// default constructor.
		Message(char* msg);// parametric constructor.
		~Message();//destructor
};

// Base class constructor
Message::Message() { 
	
	cout << "Please Enter a message: "<<endl;
	input= new char[MAX];
	cin>>input;
	cout<<input<<endl;
}

Message::Message(char* msg) {
	 input= new char[MAX];
	 strcpy(input,msg);
	 if(input == NULL)
		cerr << "Error in memory allocation";
	
}


Message::~Message() {
	delete[] input;
}

void Message::print(void) {
	
	cout << "Orignal text : " << input << endl;

}

class morseCodeMessage : public Message{ // morseCodeMessage is derived from class Message
	protected:
	
	private:
		string *morse_msg;
		void translate();
	public:
		void print();
		morseCodeMessage();
		~morseCodeMessage();
};
// Base class constructor
morseCodeMessage::morseCodeMessage() { 
	
	//cout << "Initializing morse code generator "<<endl;
	morse_msg= new string[strlen(input)];
	//cin>>input;
	//cout<<input<<endl;
	translate();
	print();
}


morseCodeMessage::~morseCodeMessage() {
	delete[] morse_msg;
}
void morseCodeMessage::translate() {
	
	for(int i=0; i<strlen(input); i++)
	{
		for(int j=0; j<number; j++)
		{
			if(*(input+i) == *(Letters+j))
			{
				morse_msg[i] = morsecode[j];
				break;
			}
		}
	}
}

void morseCodeMessage::print() {
	cout << "Original text: " << input << endl;
	cout << "Morse code: ";
	for(int i=0; i<strlen(input); i++)
	{
		cout << morse_msg[i];
	}
	cout << endl;
	cout << endl;
}

class messageStack {
	public:
		
		Message *stack[10]; 
		messageStack(Message *obj);
		int sti;
		int num_obj;
		void pop();         //LIFO
		void push(Message *); //LIFO
		void printStack();

};

messageStack::messageStack(Message *m) {
	sti = 9;
	num_obj = 0;
	push(m);
}
void messageStack::printStack(void) {
	cout << "Stack top index: " << sti << endl;
	cout << "-------------------" << endl;
	
	for(int i=sti; i<10; i++)
	{
		cout << "Current index: " << i << endl;
	}
}
		

void messageStack::pop(void) {
	if(num_obj == 0)
	{
		sti = 10;
		return;
	}
	else
	{
		num_obj--;
		(sti > 10) ? sti=10 : sti++;
	}
}


void messageStack::push(Message *m) {
	if(num_obj == 0)
	{
		stack[sti] = m;
	}
	else
	{
		if(sti == 0)
		{
			cout << "Stack full\n"; 
			return;
		}
		stack[--sti] = m;
	}
	num_obj++;

	}

	
	

int main(int argc, char **argv) {

	if(argc == 1) 
	{
		cout<<"default constructor"<<endl;
		Message m1;
		m1.print();

	}
	else{
		cout<<"parametric constructor"<<endl;
		Message m2=Message(argv[1]);
		m2.print();
	}
	//cout<<"would you like to tranfer it to morse code? Y/N? "<<endl;
	//char a;
	//cin>>a;
	//if(a=='Y'||a=='y')
	//{
		Message m3 = morseCodeMessage();
		//morseCodeMessage m3= input;
		//morseCodeMessage();
	//}
	//else
	//	return 0;
	messageStack ms1 = messageStack(&m3);
	Message m4;
	morseCodeMessage m5 = morseCodeMessage();
	//Message m5;
	ms1.push(&m4);
	ms1.push(&m5);

	ms1.printStack();
	
	ms1.pop();
	ms1.printStack();


	return 0;
}


