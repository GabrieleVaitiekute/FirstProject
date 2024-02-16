#include <iostream>
#include <climits>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <random>
#include <string>

using namespace std;
random_device rd;
mt19937 generuoti(random_device{}());

uniform_int_distribution<int> dis(1, 10);

uniform_int_distribution<int> dis_lytis(0, 1);
string vardaiV[] = { "Jonas", "Petras", "Antanas", "Juozas", "Kazys", "Darius", "Linas", "Tomas", "Giedrius", "Marius" };
string vardaiM[] = { "Ona", "Maryte", "Aldona", "Gabija", "Dalia", "Danute", "Asta", "Rasa", "Nijole", "Aiste", "Gabriele" };
string pavardesV[] = { "Jonaitis", "Petraitis", "Antanaitis", "Juozaitis", "Kaziukaitis", "Dariukaitis", "Linaitis", "Tomaitis", "Giedraitis", "Mariukaitis" };
string pavardesM[] = { "Jonaite", "Petraityte", "Antanaite", "Juozaite", "Kaziukaite", "Dariukaite", "Linaite", "Tomaite", "Giedraite", "Mariukaite", "Antaniene", "Jonaitiene", "Antaniene"};

char TaipNePaz;
char TaipNe;

struct studentas
{
	string vardas;
	string pavarde;
	int* ND;
	int EGZ = 0;
	double GalutinisV = 0;
	double GalutinisM = 0;
	int n = 0;//namu darbu kiekis
	int talpa;
};

void DydzioKeitimasS(int &MAX, int m, studentas*& S)
{
	int NaujaTalpa = MAX * 2;
	studentas *naujas_S = new studentas[NaujaTalpa];
	for (int i = 0; i < m; ++i)
	{
		naujas_S[i] = S[i];
	}
	delete[] S;
	S = naujas_S;
	MAX = NaujaTalpa;
}

void DydzioKeitimasND( int m, studentas*& S)
{
	int NaujaTalpaND = S[m].talpa * 2;
	
		int* naujas_ND = new int[NaujaTalpaND];
		for (int j = 0; j < S[m].n; ++j) 
		{
			naujas_ND[j] = S[m].ND[j];
		}
		delete[] S[m].ND; 
		S[m].ND = naujas_ND; 
		S[m].talpa = NaujaTalpaND;

}

void NetinkamasSimbolis(char& ivestis)
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
	cout << "Ivestas netinkamas simbolis. Bandykite dar karta: ";
	cin >> ivestis; 
} 

void NetinkamasString(string& ivestis)
{
	cin.clear(); 
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
	cout << "Ivesti netinkami duomenys (Negali buti skaiciu ar specialiuju zenklu).Bandykite dar karta: ";
	cin >> ivestis;
}

void NetinkamasInt (int& ivestis)
{
	cin.clear(); 
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
	cout << "Ivestas netinkamas skaitmuo. Bandykite dar karta: ";
	cin >> ivestis;
}

void GeneruotiNDPazymius(int m, studentas*& S)
{
	S[m].talpa = 1;
	S[m].ND = new int[S[m].talpa];

	do//generuojami ND pazymiai
	{
		if (S[m].n == S[m].talpa)//tikrinama ar reikia keisti dydi
		{
			DydzioKeitimasND(m, S);

		}
		S[m].ND[S[m].n] = dis(generuoti);
		cout << endl << "Sugeneruotas pazymys: " << S[m].ND[S[m].n] << endl;
		S[m].n++;
		cout << "Ar norite sugeneruoti dar viena pazymi? (iveskite T, jei taip , N, jei ne): ";
		cin >> TaipNePaz;
		while (TaipNePaz != 'T' && TaipNePaz != 'N')//tikrinama ar ivestas tinkamas simbolis
		{
			NetinkamasSimbolis(TaipNePaz);
		}

	} while (TaipNePaz == 'T');

}

void VarduIvedimas(int m, studentas*& S)
{
	cout << endl << "Iveskite studento varda: ";
	cin >> S[m].vardas;
	while (!all_of(S[m].vardas.begin(), S[m].vardas.end(), ::isalpha))
	{

		if (!all_of(S[m].vardas.begin(), S[m].vardas.end(), ::isalpha))
		{
			NetinkamasString(S[m].vardas);
		}
	}

	cout << endl << "Iveskite studento pavarde: ";
	cin >> S[m].pavarde;
	while (!all_of(S[m].pavarde.begin(), S[m].pavarde.end(), ::isalpha))
	{

		if (!all_of(S[m].pavarde.begin(), S[m].pavarde.end(), ::isalpha))
		{
			NetinkamasString(S[m].pavarde);
		}
	}

}

void GeneruotiVardusV(int m, studentas* S)
{
	S[m].vardas = vardaiV[dis(generuoti) % 10];
	S[m].pavarde = pavardesV[dis(generuoti) % 10];
}

void GeneruotiVardusM(int m, studentas* S)
{
	S[m].vardas = vardaiM[dis(generuoti) % 10];
	S[m].pavarde = pavardesM[dis(generuoti) % 10];
}

void Rezultatai(int m, studentas* S)
{
	char budas;
	cout << endl << "Kaip norite apskaiciuoti galutini bala? (iveskite M - jei su mediana, V su vidukriu) ";
	cin >> budas;
	while (budas != 'M' && budas != 'V')
	{
		NetinkamasSimbolis(budas);
	}

	if (budas == 'V')
	{

		for (int i = 0; i < m; i++)
		{
			double suma = 0.0;
			for (int j = 0; j < S[i].n; j++)
			{
				suma += S[i].ND[j];
			}
			S[i].GalutinisV = 0.4 * suma / S[i].n + 0.6 * S[i].EGZ;
		}
	}

	if (budas == 'M')
	{
		for (int i = 0; i < m; i++)
		{
			if (S[i].n - 1 == 0)
				S[i].GalutinisM = 0.4 * S[i].ND[0] + 0.6 * S[i].EGZ;

			if (S[i].n - 1 > 0)
			{
				sort(S[i].ND, S[i].ND + S[i].n);
				if (S[i].n % 2 == 0)
				{
					int m1 = round(S[i].n / 2);
					int m2 = m1 - 1;
					double medianaD = (S[i].ND[m1] + S[i].ND[m2]) / 2.0;
					S[i].GalutinisM = 0.4 * medianaD + 0.6 * S[i].EGZ;
				}
				if (S[i].n % 2 != 0)
				{
					int mediana = round(S[i].n / 2);
					S[i].GalutinisM = 0.4 * S[i].ND[mediana] + 0.6 * S[i].EGZ;
				}
			}


		}
	}
	\
	//rezultatu spausdinimas
	for (int i = 0; i < m; i++)
	{
		if (budas == 'V')
		{
			if (i == 0)
				cout << endl << setw(5) << "Nr." << setw(25) << "Pavarde" << setw(25) << "Vardas" << setw(25) << "Galutinis (Vid.)" << endl << setfill('-') << setw(90) << "-" << setfill(' ') << endl;

			cout << setw(5) << i + 1 << setw(25) << S[i].pavarde << setw(25) << S[i].vardas << setw(25) << setprecision(3) << S[i].GalutinisV << endl;
		}
		if (budas == 'M')
		{
			if (i == 0)
				cout << endl << setw(5) << "Nr." << setw(25) << "Pavarde" << setw(25) << "Vardas" << setw(25) << "Galutinis (Med.)" << endl << setfill('-') << setw(90) << "-" << setfill(' ') << endl;

			cout << setw(5) << i + 1 << setw(25) << S[i].pavarde << setw(25) << S[i].vardas << setw(25) << setprecision(3) << S[i].GalutinisM << endl;
		}
	}
	for (int i = 0; i < m; i++)
	{
		delete[] S[i].ND;
	}
		
	delete[] S;
}

int main()
{

	cout << "Pasirinkite veiksma:\n 1. Suvesti visus studentu duomenis\n 2. Sugeneruoti tik studentu pazymius\n 3. Sugeneruoti studentu vardus ir pazymius\n 4. Baigti darba\n Iveskite pasirinkimo numeri: ";
	int Pasirinkimas;
	cin >> Pasirinkimas;
	while (Pasirinkimas != 1 && Pasirinkimas != 2 && Pasirinkimas != 3 && Pasirinkimas != 4)
	{
		NetinkamasInt(Pasirinkimas);
	}
	int m = 0;
	int MAX = 1;
	studentas* S = new studentas[MAX];

	if (Pasirinkimas == 1)
	{
		do
		{

			if (m == MAX) //tikrinama ar reikia keisti dydi
			{ 
				DydzioKeitimasS(MAX, m, S);
				
			}
			VarduIvedimas(m, S);
			cout << endl << "Iveskite namu darbu pazymi: ";
			S[m].talpa = 1;
			S[m].ND = new int[S[m].talpa];
			
			do
			{
				if (S[m].n == S[m].talpa)//tikrinama ar reikia keisti dydi
				{
					DydzioKeitimasND( m, S);

				}
				int pazymys;
				cin >> pazymys;//ivedami pazymiai
				while (cin.fail() || pazymys < 1 || pazymys > 10)
				{
					NetinkamasInt(pazymys);
				}
				S[m].ND[S[m].n] = pazymys;

				S[m].n++;
				cout << "Ar norite ivesti dar viena pazymi? (T jei taip , N - ne): ";
				cin >> TaipNePaz;
				while (TaipNePaz != 'T' && TaipNePaz != 'N')//tikrinama ar ivestas tinkamas simbolis
				{
					NetinkamasSimbolis(TaipNePaz);
				}

				if (TaipNePaz == 'T') cout << endl << "Iveskite namu darbu pazymi: ";

			} while (TaipNePaz == 'T');

			cout << endl << "Iveskite egzamino pazymi: ";
			cin >> S[m].EGZ;
			while (cin.fail() || S[m].EGZ < 1 || S[m].EGZ > 10)
			{
				NetinkamasInt(S[m].EGZ);
			}
			cout << endl << "Ar norite ivesti dar viena studenta? (T jei taip , N - ne): ";
			m++;
			cin >> TaipNe;
			while (TaipNe != 'T' && TaipNe != 'N')//tikrinama ar ivestas tinkamas simbolis
			{
				NetinkamasSimbolis(TaipNe);
			}

		} while (TaipNe == 'T');

		Rezultatai(m, S);//apskaiciuojami ir spausdinami rezultatai
	}
	if (Pasirinkimas == 2 )
	{
		do
		{
			if (m == MAX)//tikrinama ar reikia keisti dydi
			{
				DydzioKeitimasS(MAX, m, S);

			}

			VarduIvedimas(m, S);

			GeneruotiNDPazymius(m,S);//generuojami pazymiai

			S[m].EGZ = dis(generuoti);//sugeneruojamas egzamino balas
			cout << endl << "Sugeneruotas egzamino pazymys: " << S[m].EGZ;
			m++;
			cout << endl << endl << "Ar norite ivesti dar viena studenta? (T jei taip , N - ne): ";
			cin >> TaipNe;
			while (TaipNe != 'T' && TaipNe != 'N')//tikrinama ar ivestas tinkamas simbolis
			{
				NetinkamasSimbolis(TaipNe);
			}

		} while (TaipNe == 'T');

		Rezultatai(m, S);//apskaiciuojami ir spausdinami rezultatai

	}
	if (Pasirinkimas == 3)
	{

		do
		{
			if (m == MAX)//tikrinama ar reikia keisti dydi
			{
				DydzioKeitimasS(MAX, m, S);

			}
			int lytis = dis_lytis(generuoti);
			
			if (lytis == 0)
			{
				GeneruotiVardusV(m, S);
			}	
			else
			{ 
				GeneruotiVardusM(m, S);
			}
			cout << endl << "Sugeneruotas vardas ir pavarde: " << S[m].vardas << " " << S[m].pavarde << endl;
			
			GeneruotiNDPazymius(m, S);//generuojami pazymiai
			
			S[m].EGZ = dis(generuoti);//sugeneruojamas egzamino balas
			cout << endl << "Sugeneruotas egzamino pazymys: " << S[m].EGZ;
			
			m++;
			cout << endl << endl << "Ar norite ivesti dar viena studenta? (T jei taip , N - ne): ";
			cin >> TaipNe;
			while (TaipNe != 'T' && TaipNe != 'N')//tikrinama ar ivestas tinkamas simbolis
			{
				NetinkamasSimbolis(TaipNe);
			}

		} while (TaipNe == 'T');

		Rezultatai(m, S);//apskaiciuojami ir spausdinami rezultatai
	}
	if (Pasirinkimas == 4)
		cout << endl << "Darbas baigtas";
	return 0;
}
