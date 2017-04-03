#include <iostream>
#include <string>


using namespace std;
#define MAX_ROLL 6
#define NUM_LETTERS 26

string Letters = "abcdefghijklmnopqrstuvwxyz";
string morseCode[] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." };


class Message { 
	protected: string msg;

	public:
		virtual void printInfo(void);
		
		Message();// default Constructors
		Message(string m); // parametric Constructors
		
		~Message(); //Destructor
};

Message::Message() { 
	
	cout << "Enter a message: ";// Empty constructor ask user for input:
	cin >> msg;
}

Message::Message(string m) {
	
	msg = m;// Get user input from command line arguments
}

void Message::printInfo(void) {
	
	cout << "Original text: " << msg << endl; 
	cout << endl;
}

Message::~Message() {
}
	


class morseCodeMessage : public Message {
	private:
		string *translated_msg;
		void translate();
	public:

		void printInfo();// Constructor
		
		morseCodeMessage();// Constructor
		
		~morseCodeMessage();// Destructor
};

morseCodeMessage::morseCodeMessage() {
	translated_msg = new string[msg.length()];
	translate();
}

morseCodeMessage::~morseCodeMessage() {
	delete[] translated_msg;
}


void morseCodeMessage::translate() {
	for(int i=0; i<msg.length(); i++)
	{
		for(int j=0; j<NUM_LETTERS; j++)
		{
			if(msg[i] == Letters[j])
			{
				translated_msg[i] = morseCode[j];
				break;
			}
		}
	}
}
		

void morseCodeMessage::printInfo() {
	cout << "Original text: " << msg << endl;
	cout << "Morse code: ";
	for(int i=0; i<msg.length(); i++)
	{
		cout << translated_msg[i];
	}
	cout << endl;
	cout << endl;
}

class messageStack {
	public:
		
		Message *stack[10]; 
		messageStack(Message *);
		int stack_top_index;
		int num_obj;
		
		void pop();         //LIFO
		void push(Message *); //LIFO
		void printStack();
	private:

};

messageStack::messageStack(Message *m) {
	stack_top_index = 9;
	num_obj = 0;
	push(m);
}

void messageStack::printStack(void) {
	cout << "Stack top index: " << stack_top_index << endl;
	cout << "-------------------" << endl;
	
	for(int i=stack_top_index; i<10; i++)
	{
		cout << "Current index: " << i << endl;
		stack[i]->printInfo();
	}
}
		

void messageStack::pop(void) {
	if(num_obj == 0)
	{
		stack_top_index = 9;
		cout << "Stack empty\n";
		return;
	}
	else
	{
		num_obj--;
		(stack_top_index > 9) ? stack_top_index=9 : stack_top_index++;
	}
}


void messageStack::push(Message *m) {
	if(num_obj == 0)
	{
		stack[stack_top_index] = m;
	}
	else
	{
		if(stack_top_index == 0)
		{
			cout << "Stack full\n"; 
			return;
		}
		stack[--stack_top_index] = m;
	}
	num_obj++;

	}


int main(int argc, char **argv) {

	if(argc > 1) 
	{// base class demonstratration
		
		
		Message m1 = Message(argv[1]);
		m1.printInfo();

	}

	// Ask user for message to translate
	morseCodeMessage m1 = morseCodeMessage();
	m1.printInfo();
	morseCodeMessage m2 = morseCodeMessage();
	morseCodeMessage m3 = morseCodeMessage();


	messageStack ms1 = messageStack(&m1);
	ms1.push(&m2);
	ms1.push(&m3);

	ms1.printStack();
	
	ms1.pop();
	ms1.printStack();
	ms1.pop();
	ms1.printStack();

	return 0;
}

