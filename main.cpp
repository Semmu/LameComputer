#include "computer.h"

/**
 * TESZT 1
 * Egyszerű regisztermanipuláció (írás és olvasás) tesztelése.
 *
 * Bemenetként egy egész számot vár amit utána rögtön kiír.
 */
void Test_1()
{
	Computer c(1, 2);
	Register *r = c.new_register();

	c	<< new REA(r)
		<< new WRI(r);

	c.execute();
}







/**
 * TESZT 2
 * Négyzetszám generáló megadható határokkal.
 *
 * Két egész számot vár bemenetként és a kettő között lévő
 * számokat és négyzeteiket kiírja.
 */
void Test_2()
{
	Computer c(10, 1000);
	Register *from = c.new_register(),
			 *to = c.new_register(),
			 *count = c.new_register(),
			 *result = c.new_register();


	c	<< new TXT("Negyzetszam generalo.\n")
		<< new TXT("Add meg az also korlatot: ")
		<< new REA(from)
		<< new TXT("Add meg a felso korlatot: ")
		<< new REA(to)
		<< new INC(to)
		<< new TXT("\n")

		<< new SET(result)
		<< new CPY(count, from)
		<< new ADD(result, from)
		<< new DEC(count)
		<< new JNZ(-2)
		<< new WRI(from)
		<< new TXT(" negyzete = ")
		<< new WRI(result)
		<< new TXT("\n")

		<< new INC(from)
		<< new CMP(from, to)
		<< new JNE(-11);

	c.execute();
}






/**
 * TESZT 3
 * Túl sok regiszter igénylésének tesztelése.
 *
 * Egy összesen 1 regiszterrel rendelkező számítógép "túlterhelése"
 * egy második regiszter lekérésével.
 */
void Test_3()
{
	Computer c(1, 1);
	Register *r1 = c.new_register();

	// !
	Register *r2 = c.new_register();

	c.execute();
}






/**
 * TESZT 4
 * Túl sok parancs betöltése a számítógépbe.
 *
 * Egy összesen 1 utasításhellyel rendelkező számítógépbe
 * túl sok parancs betöltése.
 */
void Test_4()
{
	Computer c(1, 1);
	Register *r1 = c.new_register();
	c << new SET(r1, 5);

	// !
	c << new INC(r1, 6);

	c.execute();
}







/**
 * TESZT 5
 * Hibás programkód tesztelése érvénytelen helyre ugrással.
 *
 * Az alábbi programkód hibás, mert érvénytelen utasításra próbál ugrani.
 * Erre kivételdobással reagál a Computer osztály.
 */
void Test_5()
{
	Computer c(10, 10);
	Register *a = c.new_register();

	c << new SET(a, 0)

	  // !
	  << new JIZ(5);

	c.execute();
}

int main()
{
	try
	{
		int i;
		std::cin >> i;
		std::cin.ignore(500, '\n');
		std::cout << std::endl << i << ". teszteset inditasa:" << std::endl;

		switch (i)
		{
			case 1:
				Test_1();
			break;

			case 2:
				Test_2();
			break;

			case 3:
				Test_3();
			break;

			case 4:
				Test_4();
			break;

			case 5:
				Test_5();
			break;

			default:
				std::cerr << "Nics ilyen teszteset!" << std::endl;
		}
	}
	catch (std::string e)
	{
		std::cerr << "[ERROR] " << e << std::endl;
	}

	return 0;
}