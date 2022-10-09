#include "MatrixGraph.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include "point_belongs.h"
#include "Province.h"
#include "Map.h"
#include <fstream>
//������������ ����� ��� ����� ��������� ��� ��������
void FillProv(std::vector <sf::ConvexShape>& ThrPolyg, std::vector<Province>& TempV, sf::RenderWindow& Twindow) {
    for (int i = 0; i < ThrPolyg.size(); i++) {
        ThrPolyg[i].setOutlineColor(sf::Color::Red);
        ThrPolyg[i].setOutlineThickness(5);
        Twindow.draw(ThrPolyg[i]);
        std::cout << "polygon " << i << "\n";

        buldings TempB;
        int CH1;
        std::cout << "Enter buldings\n\n2) City\n1) Town\n0) Country\n";
        std::cin >> CH1;
        switch (CH1) {
        case 0:
            TempB = Country;
        case 1:
            TempB = Town;
        case 2:
            TempB = City;
        }

        trees TempTr;
        std::cout << "Enter trees\n\n2) Forest\n1) Grove\n0) Field\n";
        std::cin >> CH1;
        switch (CH1) {
        case 0:
            TempTr = Field;
        case 1:
            TempTr = Grove;
        case 2:
            TempTr = Forest;

        }

        relief TempR;
        std::cout << "Enter relief\n\n2) Mountains\n1) Hills\n0) Plain\n";
        std::cin >> CH1;
        switch (CH1) {
        case 0:
            TempR = Plain;
        case 1:
            TempR = Hills;
        case 2:
            TempR = Mountains;

        }

        wet TempW;
        std::cout << "Enter wet\n\n1) Swamp\n0) Normal\n-1) Dust\n";
        std::cin >> CH1;
        switch (CH1) {
        case -1:
            TempW = Swamp;
        case 0:
            TempW = Normal;
        case 1:
            TempW = Dust;

        }

        bool RB;
        std::cout << "Enter RiverBank\n\n";
        std::cin >> RB;

        Province A(ThrPolyg[i], TempB, TempTr, TempR, TempW, RB);
        TempV.push_back(A);
    }
}

int main() {
    //������� �����
    sf::Image map_img;
    map_img.loadFromFile("images/map.jpg");
    sf::Texture map_tex;
    map_tex.loadFromImage(map_img);
    sf::Sprite map;

    map.setTexture(map_tex);
    map.setScale(1.f, 1.f);
    map.setPosition(0.f, 0.f);

    //������ ������������� �������
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    //������� ����
    sf::RenderWindow window(sf::VideoMode(20.f, 20.f), "Game_Map_Painter", sf::Style::Fullscreen);
    // window.setFramerateLimit(60);
     //����������� ���� 2� ������ � �� �������� ������ ����������� ������������� ����������
    sf::View view(sf::Vector2f(map.getLocalBounds().width / 2, map.getLocalBounds().height / 2), sf::Vector2f(modes[0].width, modes[0].height));

    //���� ������ ����� 
    std::string path = "Map.txt";

    //������� ��� ����������
    std::vector<Province> Temp;
    int ind = 0;

    //��� ���-����������
    float speed = 1;
    int zoom = 0;
    //��� ����� � �������� ���������

    bool AddPolyg = false;
    bool F2 = false;
    bool PointMode = false;

    //����� �� �������

    bool F5 = false;

    //���� � ������
    bool F3 = false;
    bool F4 = false;
    bool DelPolyg = false;
    int Point_count = 0;
    std::vector <sf::ConvexShape> Polygons(0);
    //��� ����� ��������
    int grid_step = 10;
    //������� ����� ���������
    int coloriter = 0;

    //������� ����
    while (window.isOpen())
    {
        window.clear();
        window.setView(view);
        window.draw(map);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();

            }
            //�������� ���� ���������������
            if (event.type == sf::Event::MouseWheelScrolled)
            {

                //��������� ���� - ��������� �����
                if (event.mouseWheelScroll.delta == -1 && zoom > -3)
                {
                    speed = speed * 1.25;//����������� �������� ���������
                    zoom--;
                    view.setSize(view.getSize().x * 1.25, view.getSize().y * 1.25);


                }
                //��������� ����� - ��������� �����
                if (event.mouseWheelScroll.delta == 1 && zoom < 6)
                {
                    speed = speed * 0.8;//����������� �������� ���������
                    zoom++;
                    view.setSize(view.getSize().x * 0.8, view.getSize().y * 0.8);


                }


                //��������� ������ �� ����� �����
                if (view.getCenter().x - view.getSize().x / 2 < 0)
                    view.setCenter(view.getSize().x / 2, view.getCenter().y);
                //��������� ������ �� ����� ������
                if (view.getCenter().x + view.getSize().x / 2 > map.getLocalBounds().width)
                    view.setCenter(map.getLocalBounds().width - view.getSize().x / 2, view.getCenter().y);
                //��������� ������ �� ����� ������
                if (view.getCenter().y - view.getSize().y / 2 < 0)
                    view.setCenter(view.getCenter().x, view.getSize().y / 2);
                //��������� ������ �� ����� �����
                if (view.getCenter().y + view.getSize().y / 2 > map.getLocalBounds().height)
                    view.setCenter(view.getCenter().x, map.getLocalBounds().height - view.getSize().y / 2);
            }


            //������� ������ (��������� ���������)


            //���������� ���������
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
                AddPolyg = true;
            if (AddPolyg)
            {

                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
                   
                    Point_count = 0;
                    AddPolyg = false;
                    sf::ConvexShape a(0);
                    a.setOutlineColor(sf::Color::Black);
                    a.setOutlineThickness(-0.25);
                    switch (coloriter % 8) {
                    case 0:

                        a.setFillColor(sf::Color::Color(255, 255, 0, 100));
                        break;
                    case 1:
                        a.setFillColor(sf::Color::Color(255, 100, 0, 100));
                        break;
                    case 2:
                        a.setFillColor(sf::Color::Color(100, 255, 0, 100));
                        break;
                    case 3:
                        a.setFillColor(sf::Color::Color(0, 255, 100, 100));
                        break;
                    case 4:
                        a.setFillColor(sf::Color::Color(0, 100, 255, 100));
                        break;
                    case 5:
                        a.setFillColor(sf::Color::Color(100, 0, 255, 100));
                        break;
                    case 6:
                        a.setFillColor(sf::Color::Color(255, 0, 100, 100));
                        break;
                    case 7:
                        a.setFillColor(sf::Color::Color(255, 100, 0, 100));
                        break;
                    default:
                        break;
                    }
                    coloriter++;
                    Polygons.push_back(a);
                    
                }
            }

            //�������� ���������
            //������� ctrl
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
            {
                //������� Z
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                {
                    DelPolyg = true;
                }
            }

            if (DelPolyg) {
                //������� Z - �������� ���������� �������� �� �������
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && Polygons.size() > 0)
                {
                    Polygons.pop_back();
                    DelPolyg = false;

                }

            }

            //���� ����� �������� �� �2
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
                F2 = true;
            }
            if (F2) {

                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
                    PointMode = !PointMode;
                    F2 = false;
                }
            }
            if (PointMode) {
                //�������� ����� �� ���
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Right && Polygons.size() > 0 && Point_count > 0)
                    {
                        Point_count = Point_count - 1;
                        Polygons[Polygons.size() - 1].setPointCount(Point_count);
                    }
                }
                //���������� ����� � ������� �� ���
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left && Polygons.size() > 0)
                    {
                        //std::cout << "Enter in mouse mod " << std::endl;

                        //����������� ���������� �����
                        Polygons[Polygons.size() - 1].setPointCount(Point_count + 1);
                        //���� �����
                        float mousex = (event.mouseButton.x) * (view.getSize().x / modes[0].width) + (view.getCenter().x - view.getSize().x / 2);
                        float mousey = (event.mouseButton.y) * (view.getSize().y / modes[0].height) + (view.getCenter().y - view.getSize().y / 2);

                        //���������� �� ���� ����������� ����� 

                        //�� x
                        if ((int)mousex % grid_step >= grid_step / 2) {
                            mousex = ((int)mousex - (int)mousex % grid_step) + grid_step;
                        }
                        else mousex = ((int)mousex - (int)mousex % grid_step);
                        //�� y
                        if ((int)mousey % grid_step >= grid_step / 2) {
                            mousey = ((int)mousey - (int)mousey % grid_step) + grid_step;
                        }
                        else mousey = ((int)mousey - (int)mousey % grid_step);

                        Polygons[Polygons.size() - 1].setPoint(Point_count, sf::Vector2f(mousex, mousey));
                        Point_count++;
                        //std::cout << mousex << " " << mousey << " " << std::endl;
                    }

                }
                //����������� �������������� ����� �������� �� ���
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Middle && Polygons.size() > 0) {
                        float mousex = (event.mouseButton.x) * (view.getSize().x / modes[0].width) + (view.getCenter().x - view.getSize().x / 2);
                        float mousey = (event.mouseButton.y) * (view.getSize().y / modes[0].height) + (view.getCenter().y - view.getSize().y / 2);

                        std::cout << point_belongs(mousex, mousey, Polygons);
                    }
                }
            }

            //���� � ������
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3) && Polygons.size() > 0) {
                F3 = true;
            }

            if (F3) {
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) {
                    F3 = false;
                    std::thread th(FillProv,std::ref(Polygons), std::ref(Temp), std::ref(window));
                    th.detach();
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F4) && Polygons.size() > 0) {
                F4 = true;
            }

            if (F4) {
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F4)) {
                    F4 = false;
                    Map M(Temp);
                    std::ofstream fout;
                    fout.open(path);
                    if (!fout.is_open()) {
                        std::cout << "������ �������� �����\n";
                    }
                    
                    else
                    {
                        
                        std::cout << "File is open\n";
                        fout.write((char*)&M,sizeof(Map));
                    }
                    fout.close();
                }
            }
                        
        }

       

        //�������� ������ �� ������� �� ����� � �������� �����
        if (event.type == sf::Event::MouseMoved)
        {
            //�������� �� ����� ������� 2� ������
            if (event.mouseMove.x == 0 && view.getCenter().x > view.getSize().x / 2)
            {
                //std::cout << "left - " << event.mouseMove.x << " " << event.mouseMove.y << std::endl;
                view.move(-speed, 0.f);
            }
            //�������� �� ������ ������� 2� ������
            if (event.mouseMove.x == modes[0].width - 1 && view.getCenter().x < map.getLocalBounds().width - view.getSize().x / 2)
            {
                //std::cout << "right - " << event.mouseMove.x << " " << event.mouseMove.y << std::endl;
                view.move(speed, 0.f);
            }
            //�������� �� ������� ������� 2� ������
            if (event.mouseMove.y == 0 && view.getCenter().y > view.getSize().y / 2)
            {
                view.move(0.f, -speed);
            }
            //�������� �� ������ ������� 2� ������
            if (event.mouseMove.y == modes[0].height - 1 && (view.getCenter().y < map.getLocalBounds().height - view.getSize().y / 2))
            {
                view.move(0.f, speed);
            }
        }

        //���������� ��������� 

        for (int i = 0; i < Polygons.size(); i++) {
            window.draw(Polygons[i]);
        }

        //��������� ����� � ������������� �����
    //�������������� ���

        int iterX = 0;
        while (iterX + grid_step < map.getGlobalBounds().width)
        {
            sf::VertexArray TemprX(sf::LinesStrip, 2);
            iterX += grid_step;
            TemprX[0].position = sf::Vector2f(iterX, 0);
            TemprX[1].position = sf::Vector2f(iterX, map.getLocalBounds().height);
            TemprX[0].color = sf::Color::Cyan;
            TemprX[1].color = sf::Color::Cyan;
            window.draw(TemprX);
        }

        //������������ ���

        int iterY = 0;
        while (iterY + grid_step < map.getGlobalBounds().height)
        {
            sf::VertexArray TemprY(sf::LinesStrip, 2);
            iterY += grid_step;
            TemprY[0].position = sf::Vector2f(0, iterY);
            TemprY[1].position = sf::Vector2f(map.getLocalBounds().width, iterY);
            TemprY[0].color = sf::Color::Cyan;
            TemprY[1].color = sf::Color::Cyan;
            window.draw(TemprY);
        }


        window.display();
    }

  

    return 0;
}