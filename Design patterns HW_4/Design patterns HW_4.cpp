#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Document
{
public:
	virtual void open() = 0;
	virtual void save(fstream& file, vector<string>& content) = 0;
	virtual void print(fstream& file) = 0;
	virtual void save_as(fstream& file, vector<string>& content) = 0;
	virtual void create() = 0;
	virtual void close(fstream& file) = 0;
	virtual void Clear_Name() = 0;
	virtual fstream& GetFile() = 0;
	virtual ~Document() {}
};


class TXT_Document : public Document
{
private:
	string filename = "";
	fstream file;
public:
	fstream& GetFile() { return file; }
	void Clear_Name() { filename = ""; }
	void open() override;
	void save(fstream& file, vector<string>& content) override;
	void print(fstream& file) override;
	void save_as(fstream& file, vector<string>& content) override;
	void close(fstream& file) override;
	void create() override;
};

class Microsoft_Word_Document : public Document
{
private:
	string filename = "";
	fstream file;
public:
	fstream& GetFile() { return file; }
	void Clear_Name() { filename = ""; }
	void open() override;
	void save(fstream& file, vector<string>& content) override;
	void print(fstream& file) override;
	void save_as(fstream& file, vector<string>& content) override;
	void close(fstream& file) override;
	void create() override;
};

class DocumentFactory
{
public:
	virtual Document* createDocument() = 0;
	virtual ~DocumentFactory() {}
};

class TXT_DocumentFactory : public DocumentFactory {
public:
	Document* createDocument() override {
		return new TXT_Document();
	}
};

class Microsoft_Word_DocumentFactory : public DocumentFactory {
public:
	Document* createDocument() override {
		return new Microsoft_Word_Document();
	}
};

void func_menu();
void func_txt();
void func_doc();


int main()
{
	func_menu();
}

void TXT_Document::open()
{
	if (!file.is_open())
	{
		cout << "Enter the name file\n";
		if (filename.empty())
		{
			cin.ignore();
			getline(cin, filename);
			filename = filename + ".txt";
			system("cls");
		}
		file.open(filename, ios::in);
		if (file.is_open())
		{
			print(file);
		}
		else
		{
			cout << "Error. File not found\n";
			filename = "";
			system("pause");
			system("cls");
		}
	}
	else throw range_error("Error. File already opened");
}

void TXT_Document::save(fstream& file, vector<string>& content)
{
	
	file.open(filename, ios::app);

	if (file.is_open() && !content.empty())
	{
		file.open(filename, ios::app);
		for (string& line : content)
		{
			file << line << endl;
		}
	}
	cout << "File saved: " << filename << endl;
	close(file);
}

void TXT_Document::print(fstream& file)
{
	if (file.is_open())
	{
		std::string line;
		cout << "Content of " << filename << ":" << endl;
		while (getline(file, line)) {
			cout << line << endl;
		}
	}
	else
	{
		throw range_error("Error of read file");
	}
}

void TXT_Document::save_as(fstream& file, vector<string>& content)
{
	string l = ""; vector<string> tmp;
	file.open(filename, ios::in);
	if (file.is_open())
	{
		while (!file.eof())
		{
			getline(file, l);
			tmp.push_back(l);
		}
	}
	file.close();
	string tmp_name;
	cout << "Enter to new name for saved file : ";
	cin.ignore();
	getline(cin, tmp_name);
	filename = tmp_name + ".txt";
	file.open(filename, ios::out);
	if (file.is_open())
	{
		for (string& line : tmp)
		{
			file << line << endl;
		}
		if (!content.empty())
		{
			for (string& line : content)
			{
				file << line << endl;
			}
		}
		cout << "File saved as " << tmp_name << endl;
		close(file);
	}
	else
	{
		throw range_error("No saved file with new name");
	}
}

void TXT_Document::close(fstream& file)
{
	if (file.is_open())
	{
		file.close();
		cout << "File closed: " << filename << endl;
		filename = "";
	}
	else
	{
		cout << "No files for closing....\n";
	}
}

void TXT_Document::create()
{
	cout << "Enter the name of the new file\n";
	cin.ignore();
	getline(cin, filename);
	filename = filename + ".txt";
	ofstream file(filename, ios::out);
	if (file.is_open())
	{
		cout << "File created: " << filename << endl;
		file.close();
		filename = "";
	}
	else {
		throw range_error("Error of create file");
	}
}

void Microsoft_Word_Document::open()
{
	if (!file.is_open())
	{
		cout << "Enter the name file\n";
		if (filename.empty())
		{
			cin.ignore();
			getline(cin, filename);
			filename = filename + ".doc";
			system("cls");
		}
		file.open(filename, ios::in);
		if (file.is_open())
		{
			print(file);
		}
		else
		{
			cout << "Error. File not found\n";
			filename = "";
			system("pause");
			system("cls");
		}
	}
	else throw range_error("Error. File already opened");
}

void Microsoft_Word_Document::save(fstream& file, vector<string>& content)
{
	file.open(filename, ios::app);

	if (file.is_open() && !content.empty())
	{
		file.open(filename, ios::app);
		for (string& line : content)
		{
			file << line << endl;
		}
	}
	cout << "File saved: " << filename << endl;
	close(file);
}

void Microsoft_Word_Document::print(fstream& file)
{
	if (file.is_open())
	{
		std::string line;
		cout << "Content of " << filename << ":" << endl;
		while (getline(file, line)) {
			cout << line << endl;
		}
	}
	else
	{
		throw range_error("Error of read file");
	}
}

void Microsoft_Word_Document::save_as(fstream& file, vector<string>& content)
{
	string l = ""; vector<string> tmp;
	file.open(filename, ios::in);
	if (file.is_open())
	{
		while (!file.eof())
		{
			getline(file, l);
			tmp.push_back(l);
		}
	}
	file.close();
	string tmp_name;
	cout << "Enter to new name for saved file : ";
	cin.ignore();
	getline(cin, tmp_name);
	filename = tmp_name + ".doc";
	file.open(filename, ios::out);
	if (file.is_open())
	{
		for (string& line : tmp)
		{
			file << line << endl;
		}
		if (!content.empty())
		{
			for (string& line : content)
			{
				file << line << endl;
			}
		}
		cout << "File saved as " << tmp_name << endl;
		close(file);
	}
	else
	{
		throw range_error("No saved file with new name");
	}
}

void Microsoft_Word_Document::close(fstream& file)
{
	if (file.is_open())
	{
		file.close();
		cout << "File closed: " << filename << endl;
		filename = "";
	}
	else
	{
		cout << "No files for closing....\n";
	}
}

void Microsoft_Word_Document::create()
{
	cout << "Enter the name of the new file\n";
	cin.ignore();
	getline(cin, filename);
	filename = filename + ".doc";
	ofstream file(filename, ios::out);
	if (file.is_open())
	{
		cout << "File created: " << filename << endl;
		file.close();
		filename = "";
	}
	else {
		throw range_error("Error of create file");
	}
}

void func_menu()
{
	try
	{
		vector <string> content;
		char menu{}; bool flag = false;
		short mode{};
		while (!flag)
		{
			system("cls");
			cout << "\t\t\t\tFile Redactor\n" <<
				"\t\tEnter 1 to select redactor txt\n" <<
				"\t\tEnter 2 to select redactor Microsoft World\n" <<
				"\t\tEnter 3 to exit\n"
				"\t\t\tYour action : "; cin >> menu;
			while (menu != '1' && menu != '2' && menu != '3' && menu)
			{
				cout << "Error input comand\n" <<
					"Enter comand again : ";
				cin >> menu;
			}
			switch (menu)
			{
			case '1':
			{
				system("cls");
				func_txt();
			}
			break;
			case '2':
			{
				system("cls");
				func_doc();
			}
			break;
			case '3':
			{
				system("cls");
				cout << "Exit from program.....\n";
				system("pause");
				flag = true;
			}
			break;
			}
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}

void func_txt()
{
	char menu{}; bool flag = false;
	string text; vector<string> content;
	DocumentFactory* factory = new TXT_DocumentFactory();
	Document* document = factory->createDocument();
	while (!flag)
	{
		system("cls");
		cout << "\t\t\tWelcome to TXT redactor!\n" <<
			"\tEnter 1 to open the file and perform actions on it\n" <<
			"\tEnter 2 to create new file\n" <<
			"\tEnter 3 to exit\n" <<
			"Your action : "; cin >> menu;
		while (menu != '1' && menu != '2' && menu != '3' && menu)
		{
			cout << "Error input comand\n" <<
				"Enter comand again : ";
			cin >> menu;
		}
		switch (menu)
		{
		case '1':
		{
			char action{}; bool flag = false;
			while (!flag)
			{
				system("cls");
				document->open();
				if (!content.empty())
				{
					for (string& l : content)
					{
						cout << l << endl;
					}
				}
				if (!document->GetFile().is_open())
				{
					flag = true;
					break;
				}
				else document->GetFile().close();
				cout << "\n================================================================\n" <<
				    "Enter 1 to adding text to file\n" <<
					"Enter 2 to save file\n" <<
					"Enter 3 to to save file with new name\n" <<
					"Enter 4 to close file\n" <<
					"Enter 5 to exit\n" <<
					"Your action : "; cin >> action;
				while (menu != '1' && menu != '2' && menu != '3' &&
					menu != '4' && menu != '5' && menu)
				{
					cout << "Error input comand\n" <<
						"Enter comand again : ";
					cin >> menu;
				}
				switch (action)
				{
				case '1':
				{
					system("cls");
					int count{};
					cout << "Enter to count strings : ";
					cin >> count;
					while (count < 1 || count > 5 || !count)
					{
						cout << "Error input count strings\n" <<
							"Try count strings again : ";
						cin >> count;
					}
					cin.ignore();
					for (int i = 0; i < count; i++)
					{
						cout << "Enter to string " << i + 1 << " : ";
						getline(cin, text);
						content.push_back(text);
					}

				}
				break;
				case '2':
				{
					system("cls");
					document->save(document->GetFile(),content);
					system("pause");
					flag = true;
				}
				break;
				case '3':
				{
					system("cls");
					document->save_as(document->GetFile(), content);
					system("pause");
					flag = true;
				}
				break;
				case '4':
				{
					system("cls");
					char change{};
					cout << "Do I need to save the file before closing?\n" <<
						"Enter 1 if yes\n" <<
						"Enter 2 if no\n" <<
						"You action : "; cin >> change;
					while (change != '1' && change != '2' && !change)
					{
						cout << "Error input comand..." <<
							"Try again input comand : ";
						cin >> change;
					}
					switch (change)
					{
					case '1':
						system("cls");
						document->save(document->GetFile(), content);
						break;
					case '2':
						system("cls");
						cout << "Closing file......\n";
						document->Clear_Name();
						break;
					}
					system("pause");
					flag = true;
				}
				break;
				case '5':
				{
					system("cls");
					cout << "Exit from program.....\n";
					system("pause");
					flag = true;
				}
				break;
				}
			}
		}
		break;
		case '2':
		{
			system("cls");
			document->create();
			system("pause");
		}
		break;
		case '3':
		{
			system("cls");
			cout << "Exit from program.....\n";
			system("pause");
			flag = true;
		}
		break;
		}
	}
	delete factory;
	delete document;
}

void func_doc()
{
	char menu{}; bool flag = false;
	string text; vector<string> content;
	DocumentFactory* factory = new Microsoft_Word_DocumentFactory();
	Document* document = factory->createDocument();
	while (!flag)
	{
		system("cls");
		cout << "\t\t\tWelcome to redactor!\n" <<
			"\tEnter 1 to open the file and perform actions on it\n" <<
			"\tEnter 2 to create new file\n" <<
			"\tEnter 3 to exit\n" <<
			"Your action : "; cin >> menu;
		while (menu != '1' && menu != '2' && menu != '3' && menu)
		{
			cout << "Error input comand\n" <<
				"Enter comand again : ";
			cin >> menu;
		}
		switch (menu)
		{
		case '1':
		{
			char action{}; bool flag = false;
			while (!flag)
			{
				system("cls");
				document->open();
				if (!content.empty())
				{
					for (string& l : content)
					{
						cout << l << endl;
					}
				}
				if (!document->GetFile().is_open())
				{
					flag = true;
					break;
				}
				else document->GetFile().close();
				cout << "Enter 1 to adding text to file\n" <<
					"Enter 2 to save file\n" <<
					"Enter 3 to to save file with new name\n" <<
					"Enter 4 to close file\n" <<
					"Enter 5 to exit\n" <<
					"Your action : "; cin >> action;
				while (menu != '1' && menu != '2' && menu != '3' &&
					menu != '4' && menu != '5' && menu)
				{
					cout << "Error input comand\n" <<
						"Enter comand again : ";
					cin >> menu;
				}
				switch (action)
				{
				case '1':
				{
					system("cls");
					int count{};
					cout << "Enter to count strings : ";
					cin >> count;
					while (count < 1 || count > 5 || !count)
					{
						cout << "Error input count strings\n" <<
							"Try count strings again : ";
						cin >> count;
					}
					cin.ignore();
					for (int i = 0; i < count; i++)
					{
						cout << "Enter to string " << i + 1 << " : ";
						getline(cin, text);
						content.push_back(text);
					}

				}
				break;
				case '2':
				{
					system("cls");
					document->save(document->GetFile(), content);
					system("pause");
					flag = true;
				}
				break;
				case '3':
				{
					system("cls");
					document->save_as(document->GetFile(), content);
					system("pause");
					flag = true;
				}
				break;
				case '4':
				{
					system("cls");
					char change{};
					cout << "Do I need to save the file before closing?\n" <<
						"Enter 1 if yes\n" <<
						"Enter 2 if no\n" <<
						"You action : "; cin >> change;
					while (change != '1' && change != '2' && !change)
					{
						cout << "Error input comand..." <<
							"Try again input comand : ";
						cin >> change;
					}
					switch (change)
					{
					case '1':
						system("cls");
						document->save(document->GetFile(), content);
						break;
					case '2':
						system("cls");
						cout << "Closing file......\n";
						document->Clear_Name();
						break;
					}
					system("pause");
					flag = true;
				}
				break;
				case '5':
				{
					system("cls");
					cout << "Exit from program.....\n";
					system("pause");
					flag = true;
				}
				break;
				}
			}
		}
		break;
		case '2':
		{
			system("cls");
			document->create();
			system("pause");
		}
		break;
		case '3':
		{
			system("cls");
			cout << "Exit from program.....\n";
			system("pause");
			flag = true;
		}
		break;
		}
	}
	delete factory;
	delete document;
}
