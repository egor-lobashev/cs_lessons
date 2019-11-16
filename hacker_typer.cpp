#include <SFML/Graphics.hpp>
#include <fstream>


char *read_from_file(char *buffer, char *filename, int len)
{
	std::ifstream f(filename);
	f.read(buffer, len);
	f.close();
}


int file_len(char *filename)
{
	std::ifstream f(filename);

	f.seekg(0, f.end);
	int len = f.tellg();
	f.seekg(0, f.beg);

	f.close();
	return len;
}


class printed_code
{
private:
	int len, printed_len, next_number;
	char *text, *printed_text;
public:
	int number_of_strings;
	bool miss_char = false;

	printed_code(char *filename)
	{
		number_of_strings = 1;
		next_number = 0;
		len = file_len(filename);
		printed_len = len;
		text = new char[len];
		read_from_file(text, filename, len);

		printed_text = new char[len];
		for (int j=0;  j < len;  ++j)
		{
			printed_text[j] = ' ';
		} // memset() \0
	}

	char next_char()
	{
		int n = next_number;

		if (text[n] == '\n') // countSymbolInStr()
		{
			number_of_strings += 1;
		}

		printed_text[n + printed_len - len] = text[n];
		next_number += 1;

		if ((text[n] == ' ') or (text[n] == '\n')) // remove miss_char -> const SYMBOLS_PER_TAP
			miss_char = true;
		else
			miss_char = false;
	}

	void delete_first_str()
	{
		int j=0;
		while (printed_text[j] != '\n')
		{
			j++;
		}
		j++;

		// getFirstPlace()

		printed_len = printed_len - j;
		for  (int k=j; j < printed_len; ++j)
		{
			printed_text[j-k] = printed_text[j];
		}

		number_of_strings -= 1;
	}

	void show(sf::RenderWindow *window)
	{
		sf::Font font;
		font.loadFromFile("arial.ttf");
		sf::Text text(printed_text, font, 17);
		text.setPosition(70,100);
		text.setFillColor(sf::Color(255,255,255));

		window->draw(text);
	}

	~printed_code()
	{
		delete[] text;
		delete[] printed_text;
	}
};


void update_window(sf::RenderWindow *window, printed_code *printed)
{
	sf::Image background;
	background.loadFromFile("hacker_typer_background.png");
	sf::Texture background_texture;
	background_texture.loadFromImage(background);
	sf::Sprite background_sprite;
	background_sprite.setTexture(background_texture);

	window->draw(background_sprite);
	printed->show(window);
	window->display();
}


int main()
{
	printf("Hello!");
	sf::RenderWindow window(sf::VideoMode(1000, 600), "Sumo");
	char filename[] = "sumo.cpp";
	bool miss_char = false;
	printed_code printed = printed_code(filename);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				printed.next_char();
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}

		
		if (printed.miss_char)
		{
			printed.next_char();
		}			

		if (printed.number_of_strings == 24)
		{
			printed.delete_first_str();
		}


		update_window(&window, &printed);
	}
	return 0;
}
