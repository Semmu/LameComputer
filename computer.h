#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include <iostream>

struct Flags
	{ bool ZER, OFL, EQU, LIB, RIB; };

const Flags FLAGS_DEFAULT = {false, false, false, false, false};

class Computer;
class Command;

class Register
{
	private:
		unsigned char _value;

		Register() : _value(0) {};


	public:
		unsigned char& value();

		friend class Computer;
};

class Command
{
	public:
		virtual signed int execute(Flags& f) = 0;
};

class TXT : public Command
{
	private:
		const char * str;

		TXT(const TXT& c);
		TXT operator=(const TXT& c);

	public:
		TXT(const char * s) : str(s) {};
		signed int execute(Flags& f);
};

class INC : public Command
{
	private:
		Register* target;
		unsigned char amount;

		INC(const INC& c);
		INC operator=(const INC& c);

	public:
		INC(Register* t, unsigned char a = 1) : target(t), amount(a) {};
		signed int execute(Flags& f);
};

class DEC : public Command
{
	private:
		Register* target;
		unsigned char amount;

		DEC(const DEC& c);
		DEC operator=(const DEC& c);

	public:
		DEC(Register* t, unsigned char a = 1) : target(t), amount(a) {};
		signed int execute(Flags& f);
};

class ADD : public Command
{
	private:
		Register* target;
		Register* source;

		ADD(const ADD& c);
		ADD operator=(const ADD& c);

	public:
		ADD(Register* t, Register* s) : target(t), source(s) {};
		signed int execute(Flags& f);
};

class SBS : public Command
{
	private:
		Register* target;
		Register* source;

		SBS(const SBS& c);
		SBS operator=(const SBS& c);

	public:
		SBS(Register* t, Register* s) : target(t), source(s) {};
		signed int execute(Flags& f);
};

class SET : public Command
{
	private:
		Register* target;
		unsigned char value;

		SET(const SET& c);
		SET operator=(const SET& c);

	public:
		SET(Register* t, unsigned char v = 0) : target(t), value(v) {};
		signed int execute(Flags& f);
};

class WRI : public Command
{
	private:
		Register* target;

		WRI(const WRI& c);
		WRI operator=(const WRI& c);

	public:
		WRI(Register* t) : Command(), target(t) {};
		signed int execute(Flags& f);
};

class REA : public Command
{
	private:
		Register* target;

		REA(const REA& c);
		REA operator=(const REA& c);

	public:
		REA(Register* t) : target(t) {};
		signed int execute(Flags& f);
};

class CPY : public Command
{
	private:
		Register *to, *from;

		CPY(const CPY& c);
		CPY operator=(const CPY& c);

	public:
		CPY(Register* t, Register* f) : to(t), from(f) {};
		signed int execute(Flags& f);
};

class CMP : public Command
{
	private:
		Register *left, *right;

		CMP(const CMP& c);
		CMP operator=(const CMP& c);

	public:
		CMP(Register*  l, Register* r) : left(l), right(r) {};
		signed int execute(Flags& f);
};

class JIE : public Command
{
	private:
		signed int amount;

		JIE(const JIE& c);
		JIE operator=(const JIE& c);

	public:
		JIE(signed int a = -1) : amount(a) {};
		signed int execute(Flags& f);
};

class JNE : public Command
{
	private:
		signed int amount;

		JNE(const JNE& c);
		JNE operator=(const JNE& c);

	public:
		JNE(signed int a = -1) : amount(a) {};
		signed int execute(Flags& f);
};

class JLB : public Command
{
	private:
		signed int amount;

		JLB(const JLB& c);
		JLB operator=(const JLB& c);

	public:
		JLB(signed int a = -1) : amount(a) {};

		signed int execute(Flags& f);
};

class JRB : public Command
{
	private:
		signed int amount;

		JRB(const JRB& c);
		JRB operator=(const JRB& c);

	public:
		JRB(signed int a = -1) : amount(a) {};

		signed int execute(Flags& f);
};

class JIZ : public Command
{
	private:
		signed int amount;

		JIZ(const JIZ& c);
		JIZ operator=(const JIZ& c);

	public:
		JIZ(signed int a = -1) : amount(a) {};

		signed int execute(Flags& f);
};

class JNZ : public Command
{
	private:
		signed int amount;

		JNZ(const JNZ& c);
		JNZ operator=(const JNZ& c);

	public:
		JNZ(signed int a = -1) : amount(a) {};

		signed int execute(Flags& f);
};

class JIO : public Command
{
	private:
		signed int amount;

		JIO(const JIO& c);
		JIO operator=(const JIO& c);

	public:
		JIO(signed int a = -1) : amount(a) {};

		signed int execute(Flags& f);
};






class Computer
{
	private:
		Computer operator=(const Computer& c);
		Computer(const Computer& c);

		Register* registers;
		signed int registers_count,
			   registers_allocated;

		Command** commands;
		signed int commands_count,
			   commands_allocated,
			   command_executed;

		Flags flags;

	public:
		Computer(signed int reg_max = 30, signed int cmd_max = 300);
		~Computer();

		Register* new_register(unsigned char value = 0);
		void add_command(Command * cmd);

		void execute();

		Computer& operator<<(Command * c);
};

#endif