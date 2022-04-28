#pragma once
#include<iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "Matrix.h"
#include <thread>
#include <time.h>



#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27
#define TAB_KEY 9

//### This class is for creating the buttons on all windows ###
class Button {
private:
	sf::Texture texture;
	sf::Sprite button;
	std::string fname;

public:
	Button() {

	}
	Button(std::string btnname) {
		this->fname = btnname;
		texture.loadFromFile(btnname);
		button.setTexture(texture);
	}
	void setTexture(std::string fname) {
		texture.loadFromFile(fname);
	}


	void setPosition(sf::Vector2f pos) {
		button.setPosition(pos);
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(button);
	}

	bool isMouseOver(sf::RenderWindow& window) {
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float btnPosX = button.getPosition().x;
		float btnPosY = button.getPosition().y;

		float btnXPosWidth = button.getPosition().x + button.getLocalBounds().width;
		float btnYPosHeight = button.getPosition().y + button.getLocalBounds().height;

		if (mouseX < btnXPosWidth && mouseX > btnPosX && mouseY < btnYPosHeight && mouseY > btnPosY) {
			return true;
		}
		return false;

	}
};

// ### This class is for creating the Textbox Objects on the main window.###
class Textbox {

private:
	sf::Text textbox;
	std::ostringstream text;
	bool hasLimit = false;
	int limit;
	sf::Texture texture;
	sf::Sprite box;
	sf::Text title;


	void inputLogic(int charTyped) {
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY && charTyped != TAB_KEY) {
			text << static_cast<char>(charTyped);
		}
		else if (charTyped == DELETE_KEY) {
			if (text.str().length() > 0) {
				deleteLastChar();
			}
		}
		textbox.setString(text.str() + "_");
	}
	void deleteLastChar() {
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length() - 1; i++) {
			newT += t[i];
		}
		text.str("");
		text << newT;

		textbox.setString(text.str());
	}
public:
	bool isSelected = false;
	Textbox() {
	}
	Textbox(int size, sf::Color color, bool sel) {


		textbox.setCharacterSize(size);
		textbox.setFillColor(color);
		isSelected = sel;
		if (sel) {
			textbox.setString("_");
		}
		else {
		textbox.setString("");
		}

	}

	void setFont(sf::Font& font) {
		textbox.setFont(font);
		title.setFont(font);
	}
	void setPosition(sf::Vector2f pos, std::string tname) {
		textbox.setPosition(pos);
		texture.loadFromFile("imgs/textbox.png");
		box.setTexture(texture);
		box.setPosition(pos.x - 10, pos.y - 5);

		title.setString(tname);
		title.setFillColor(sf::Color::Black);
		title.setCharacterSize(20);
		title.setPosition(pos.x - 160, pos.y);

	}
	void setLimit(bool ToF) {
		hasLimit = ToF;
	}
	void setLimit(bool ToF, int lim) {
		hasLimit = ToF;
		limit = lim;
	}
	void setSelected(bool sel) {
		isSelected = sel;
		if (!sel) {
			std::string t = text.str();
			std::string newT = "";
			for (int i = 0; i < t.length(); i++) {
				newT += t[i];
			}
			textbox.setString(newT);
		}
		else {
			textbox.setString(text.str() + "_");
		}
	}
	std::string getText() {
		return text.str();
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(box);
		window.draw(textbox);
		window.draw(title);
	}
	void typedOn(sf::Event input) {
		if (isSelected) {
			int charTyped = input.text.unicode;
			if (charTyped < 128) {
				if (hasLimit) {
					if (text.str().length() <= limit) {
						inputLogic(charTyped);
					}
					else if (text.str().length() > limit && charTyped == DELETE_KEY) {
						deleteLastChar();
					}
				}
				else {
					inputLogic(charTyped);
				}
			}
		}
	}
	bool isMouseOver(sf::RenderWindow& window) {
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float boxPosX = box.getPosition().x;
		float boxPosY = box.getPosition().y;

		float boxXPosWidth = box.getPosition().x + box.getLocalBounds().width;
		float boxYPosHeight = box.getPosition().y + box.getLocalBounds().height;

		if (mouseX < boxXPosWidth && mouseX > boxPosX && mouseY < boxYPosHeight && mouseY > boxPosY) {
			return true;
		}
		return false;

	}
};

class Graphic {
private:
	sf::Vector2i origin;
	sf::Vector2i bgOrig;
	int cellSize;
	sf::Font font;
	int msize;

public:
	sf::RectangleShape bg;
	std::vector <std::pair<sf::RectangleShape, sf::Text>> cells;

	Graphic(int x, int y, int size, Matrix matrix) {
		this->origin = sf::Vector2i{ x,y };
		this->bgOrig = sf::Vector2i{ x - 3, y - 3 };
		this->font.loadFromFile("Windows Regular.ttf");
		this->msize = size;
		if (matrix.getMaxRow() > matrix.getMaxCol()) {
			this->cellSize = (size / matrix.getMaxRow());
		}
		else {
			this->cellSize = (size / matrix.getMaxCol());
		}
		bg.setSize(sf::Vector2f((matrix.getMaxCol() * cellSize) + (matrix.getMaxCol() * 5) + 3, (matrix.getMaxRow() * cellSize) + (matrix.getMaxRow() * 5) + 3)) ;
	}


	void makeGraphic(Matrix matrix) {
		std::pair<sf::RectangleShape, sf::Text> tuple;

		Node* temp = matrix.getHead();
		sf::RectangleShape cell(sf::Vector2f(cellSize + 2, cellSize + 2 ));
		bg.setPosition(bgOrig.x, bgOrig.y);
		bg.setFillColor(sf::Color(0, 0, 0));

		sf::Vector2i position;
		std::ostringstream cellData;
		sf::Text mData;
		mData.setFont(font);
		mData.setCharacterSize(cellSize * 0.85);
		for (int i = 0; i < matrix.getMaxRow(); i++) {
			for (int j = 0; j < matrix.getMaxCol(); j++) {
				if (temp != nullptr && temp->getRow() == i && (temp->getCol() == j)) {
					cellData << temp->getData();
					mData.setString(cellData.str());
					temp = temp->getNext();
				}
				else {
					cellData << "0";
					mData.setString(cellData.str());
				}
				//colors
				mData.setFillColor(sf::Color::White);
				cell.setFillColor(sf::Color(255, 255, 255));
				//positions
				position = { (origin.x + (j * cellSize) + (j * 5)), (origin.y + (i * cellSize) + (i * 5)) };
				cell.setPosition(position.x, position.y);
				mData.setPosition(position.x + (cellSize / 5), position.y);

				tuple = std::make_pair(cell, mData);
				this->cells.push_back(tuple);

				cellData.str("");
				cellData.clear();
			}
		}
	}


};













//### This Struct Contains the functions that display the main window and the result windows for addition and multiplication. ###
class RenderWindow {
	friend class Matrix;
	friend class Node;
public:
	RenderWindow() {
	}

	void RenderMain() {
		sf::Text title;
		sf::Font wFont;
		wFont.loadFromFile("Windows Regular.ttf");
		bool isAdd = false;


		sf::RenderWindow window;
		sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);


		window.create(sf::VideoMode(900, 450), "Test Text", sf::Style::Titlebar | sf::Style::Close);
		window.setPosition(centerWindow);
		window.setKeyRepeatEnabled(true);


		Textbox textbox1(20, sf::Color::Black, false);
		textbox1.setFont(wFont);
		textbox1.setPosition({ 350, 300 }, "Enter File Name 1:");
		textbox1.setLimit(true, 32);

		Textbox textbox2(20, sf::Color::Black, false);
		textbox2.setFont(wFont);
		textbox2.setPosition({ 350, 350 }, "Enter File Name 2:");
		textbox2.setLimit(true, 32);


		Button btn1("imgs/addbtn.png");
		btn1.setPosition({ 350, 400 });

		Button btn2("imgs/multbtn.png");
		btn2.setPosition({ 500, 400 });


		std::string file1;
		std::string file2;

		sf::Texture texture;
		sf::Texture addbg;
		sf::Texture multbg;

		texture.loadFromFile("imgs/bg.png");
		addbg.loadFromFile("imgs/addbg.png");
		multbg.loadFromFile("imgs/multbg.png");

		sf::Sprite sprite(texture);

		//### MAIN WINDOW ###

		while (window.isOpen()) {
			sf::Event event;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				textbox1.setSelected(false);
				textbox2.setSelected(false);
			}


			while (window.pollEvent(event)) {
				switch (event.type) {

				case sf::Event::Closed:
					window.close();

				case sf::Event::TextEntered:
					textbox1.typedOn(event);
					textbox2.typedOn(event);
					break;
				case sf::Event::MouseMoved:
					if (btn1.isMouseOver(window)) {
						btn1.setTexture("imgs/addbtnH.png");
					}
					else {
						btn1.setTexture("imgs/addbtn.png");
					}
					if (btn2.isMouseOver(window)) {
						btn2.setTexture("imgs/multbtnH.png");
					}
					else {
						btn2.setTexture("imgs/multbtn.png");
					}
					break;
				case sf::Event::MouseButtonPressed:
					if (btn1.isMouseOver(window)) {
						btn1.setTexture("imgs/addbtnP.png");
						file1 = textbox1.getText();
						file2 = textbox2.getText();
						Matrix m(file1);
						Matrix n(file2);
						Matrix result;
						result = m + n;

						//### ADDITION WINDOW ###
						isAdd = true;
						RenderWindow addR;
						window.close();
						addR.RenderResult(m, n, result, addbg, wFont);

					}
					if (btn2.isMouseOver(window)) {
						btn2.setTexture("imgs/multbtnP.png");
						file1 = textbox1.getText();
						file2 = textbox2.getText();
						Matrix m(file1);
						Matrix n(file2);
						Matrix result;
						result = m * n;

						//### MULTIPLICATION WINDOW ###
						isAdd = false;
						RenderWindow multR;
						window.close();
						multR.RenderResult(m, n, result, multbg, wFont);
					}


					if (textbox1.isMouseOver(window)) {
						textbox1.setSelected(true);
					}
					if (textbox1.isMouseOver(window) == false) {
						textbox1.setSelected(false);
					}
					if (textbox2.isMouseOver(window)) {
						textbox2.setSelected(true);
					}
					if (textbox2.isMouseOver(window) == false) {
						textbox2.setSelected(false);
					}
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Tab) {
						if (textbox1.isSelected) {
							textbox1.setSelected(false);
							textbox2.setSelected(true);
						}
						else if (textbox2.isSelected) {
							textbox2.setSelected(false);
							textbox1.setSelected(true);

						}
					}
				}


			}

			//Draw
			window.clear();
			window.draw(sprite);
			textbox1.drawTo(window);
			textbox2.drawTo(window);
			btn1.drawTo(window);
			btn2.drawTo(window);
			window.display();

		}

	}
	void RenderResult(Matrix m1, Matrix m2, Matrix result, sf::Texture bg, sf::Font font) {
		sf::RenderWindow resultWindow;
		resultWindow.setFramerateLimit(60);
		resultWindow.create(sf::VideoMode(1800, 980), "Matrix Rendering", sf::Style::Titlebar | sf::Style::Close);
		std::string filename = "output1.txt";
		sf::Sprite resultbg;
		resultbg.setTexture(bg);
		bool m1complete = false, m2complete = false;
		Graphic answer(800, 80, 700, result);
		answer.makeGraphic(result);

		Graphic matrix1(50, 75, 350, m1);
		matrix1.makeGraphic(m1);
		Graphic matrix2(50, 525, 350, m2);
		matrix2.makeGraphic(m2);
	

		Button printb("imgs/printbtn.png");
		printb.setPosition({ 1100, 900 });
		sf::Clock clock;
		std::vector<sf::RectangleShape> tempbgcells;
		int a = 0 , b = 0, c = 0;

		while (resultWindow.isOpen()) {
		std::pair<sf::RectangleShape, sf::Text> tempPair;
		sf::Text zero;
		sf::RectangleShape tempCell;
		zero.setString("0");

			sf::Time elapsed1 = clock.getElapsedTime();
			sf::Time count = sf::seconds(0.25);
			resultWindow.draw(resultbg);
			resultWindow.draw(matrix1.bg);
			resultWindow.draw(matrix2.bg);
			resultWindow.draw(answer.bg);
			for (int x = 0; x < answer.cells.size(); x++) {
				resultWindow.draw(answer.cells[x].first);
				resultWindow.draw(answer.cells[x].second);
			}
			for (int x = 0; x < matrix1.cells.size(); x++) {
				resultWindow.draw(matrix1.cells[x].first);
				resultWindow.draw(matrix1.cells[x].second);
			}

			for (int x = 0; x < matrix2.cells.size(); x++) {
				resultWindow.draw(matrix2.cells[x].first);
				resultWindow.draw(matrix2.cells[x].second);
			}

			if (elapsed1 > count && matrix1.cells[a].second.getString() != zero.getString() && a < matrix1.cells.size()) {
				matrix1.cells[a].first.setFillColor(sf::Color(0, 0, 255));
				matrix1.cells[a].second.setFillColor(sf::Color(255, 240, 0));
				a += 1;
				clock.restart();
			}
			else if (elapsed1 > count && a < matrix1.cells.size()) {
				a += 1;
			}
			if (a >= (matrix1.cells.size() - 1)) {
				m1complete = true;
			}

			if (elapsed1 > count && matrix2.cells[b].second.getString() != zero.getString() && b < matrix2.cells.size()) {
				matrix2.cells[b].first.setFillColor(sf::Color(0, 0, 255));
				matrix2.cells[b].second.setFillColor(sf::Color(255, 240, 0));
				b += 1;
				clock.restart();
			}
			else if (elapsed1 > count && b < matrix2.cells.size()) {
				b += 1;
			}
			if (b >= (matrix2.cells.size() - 1)) {
				m2complete = true;
			}
	
			if (m1complete == true) {
				if (elapsed1 > count && answer.cells[c].second.getString() != zero.getString() && c < answer.cells.size()) {
					answer.cells[c].first.setFillColor(sf::Color(0, 0, 255));
					answer.cells[c].second.setFillColor(sf::Color(255, 240, 0));
					c += 1;
					clock.restart();

				}
				else if (elapsed1 > count && c < answer.cells.size()) {
					c += 1;
				}
			}
			sf::Event addEvent;
			while (resultWindow.pollEvent(addEvent)) {
				switch (addEvent.type) {
				case sf::Event::MouseMoved:
					if (printb.isMouseOver(resultWindow)) {
						printb.setTexture("imgs/printbtnH.png");
					}
					else {
						printb.setTexture("imgs/printbtn.png");
					}
					break;
				case sf::Event::MouseButtonPressed:
					if (printb.isMouseOver(resultWindow)) {
						printb.setTexture("imgs/printbtnP.png");
						result.writeFile("out1.txt");
						std::string s;
						filename = "notepad.exe out1.txt";
						system(filename.c_str());
					}
					break;
				case sf::Event::Closed:
					resultWindow.close();
					RenderWindow main1;
					main1.RenderMain();
					break;
				}
				
			}
		printb.drawTo(resultWindow);
		resultWindow.display();
		}

	}

};

//## End
