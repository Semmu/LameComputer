#include "computer.h"


unsigned char& Register::value()
{
	return _value;
}

signed int TXT::execute(Flags& f)
{
	std::cout << str;

	return 1;
}

signed int INC::execute(Flags& f)
{
	f = FLAGS_DEFAULT;
	f.OFL = (target->value() + amount < target->value());

	target->value() = target->value() + amount;

	f.ZER = (target->value() == 0);

	return 1;
}

signed int DEC::execute(Flags& f)
{
	f = FLAGS_DEFAULT;

	f.OFL = (target->value() - amount > target->value());

	target->value() = target->value() - amount;

	f.ZER = (target->value() == 0);

	return 1;
}

signed int ADD::execute(Flags& f)
{
	f = FLAGS_DEFAULT;
	f.OFL = (target->value() + source->value() < target->value());

	target->value() += source->value();

	return 1;
}

signed int SBS::execute(Flags& f)
{
	f = FLAGS_DEFAULT;
	f.OFL = (target->value() - source->value() > target->value());

	target->value() -= source->value();

	return 1;
}

signed int SET::execute(Flags& f)
{
	f = FLAGS_DEFAULT;

	target->value() = value;

	f.ZER = (target->value() == 0);

	return 1;
}

signed int WRI::execute(Flags& f)
{
	std::cout << (int)target->value();

	return 1;
}

signed int REA::execute(Flags& f)
{
	f = FLAGS_DEFAULT;

	int v;
	std::cin >> v;
	target->value() = v;

	f.ZER = (target->value() == 0);

	return 1;
}

signed int CPY::execute(Flags& f)
{
	f = FLAGS_DEFAULT;

	to->value() = from->value();

	f.ZER = (to->value() == 0);

	return 1;
}

signed int CMP::execute(Flags& f)
{
	f = FLAGS_DEFAULT;

	if (left->value() == right->value())
		f.EQU = true;
	else
	{
		if (left->value() > right->value())
			f.LIB = true;
		else
			f.RIB = true;
	}

	f.ZER = (left->value() == 0);

	return 1;
}

signed int JIE::execute(Flags& f)
{
	return f.EQU ? amount : 1;
}

signed int JNE::execute(Flags& f)
{
	return f.EQU ? 1 : amount;
}

signed int JLB::execute(Flags& f)
{
	return f.LIB ? amount : 1;
}

signed int JRB::execute(Flags& f)
{
	return f.RIB ? amount : 1;
}

signed int JIZ::execute(Flags& f)
{
	return f.ZER ? amount : 1;
}

signed int JNZ::execute(Flags& f)
{
	return f.ZER ? 1 : amount;
}

signed int JIO::execute(Flags& f)
{
	return f.OFL ? amount : 1;
}




Computer::Computer(signed int reg_max, signed int cmd_max) : flags(FLAGS_DEFAULT), registers_allocated(reg_max), registers_count(0), commands_count(0), commands_allocated(cmd_max)
{
	registers = new Register[registers_allocated];
	commands = new Command*[commands_allocated];
}

Computer::~Computer()
{
	delete [] registers;

	for (signed int i = 0; i < commands_count; i++)
		delete [] commands[i];

	delete [] commands;
}

Register* Computer::new_register(unsigned char value)
{
	if (registers_count + 1 > registers_allocated)
		throw std::string("Computer::new_register : not enough registers.");

	registers[registers_count].value() = value;
	registers_count++;
	return &registers[registers_count - 1];
}

void Computer::add_command(Command* cmd)
{
	if (commands_count + 1 > commands_allocated)
	{
		delete cmd;
		throw std::string("Computer::add_command : too much commands.");
	}

	commands[commands_count] = cmd;
	commands_count++;
}

Computer& Computer::operator<<(Command* cmd)
{
	add_command(cmd);
	return *this;
}

void Computer::execute()
{
	command_executed = 0;
	while (command_executed < commands_count)
	{
		signed int jump_dst = commands[command_executed]->execute(flags);

		if (command_executed + jump_dst > commands_count)
			throw std::string("Computer::execute : invalid jump destination.");
		else
			command_executed += jump_dst;
	}
}