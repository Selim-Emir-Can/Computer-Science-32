#ifndef UTILITY_INCLUDED
#define UTILITY_INCLUDED

#include"globals.h"
#include<string>
#include<iostream>
#include<vector>
class Game;

class OnCrossData
{
public:
    OnCrossData();
    OnCrossData(Point point, int length, Direction dir);
    Point getpoint() const;
    int getlength() const;
    Direction getdir() const;
private:
    Point m_point;
    int m_length;
    Direction m_dir;
};
class Ship
{
public:
	Ship(int length, char symbol, std::string name, int shipId);
    std::string getname() const;
    char getsymbol() const;
    int getlength() const;
    int getshipId() const;
private:
	std::string m_name;
	char m_symbol;
	int m_length;
    int m_shipId;
};
template < class T>
class Node
{
public:
    Node() {}
    Node(T theData, Node<T>* theLink) : data(theData), link(theLink) {}
    Node<T>* getLink() const { return link; }
    const T getData() const { return data; }
    void setData(const T& theData) { data = theData; }
    void setLink(Node<T>* pointer) { link = pointer; }
private:
    T data;
    Node<T>* link;
};

class Orientations
{
public:
    Orientations();
    Orientations(int rows, int cols, int shiplength, Point point);
    Orientations(int rows, int cols, int shiplength, Point point, std::vector<Point> Attacked);
    bool isValid(Point p, int rows, int cols) const { return((p.r >= 0) && (p.r < rows) && (p.c >= 0) && (p.c < cols)); }
    bool isValid(Point p, std::vector<Point> Attacked) const;
    bool isWholeShipValid(int m_rows, int m_cols, int shiplength, Point point, Direction Dir);  // checks if the ship will fit on the board
    bool isWholeShipValid(int rows, int cols, int shiplength, Point point, Direction Dir, std::vector<Point> Attacked);
    bool isPointOnShip(Point point, OnCrossData Ship);  // checks if point is on the ship
    int reEvaluateOrientations(bool HitOrMiss, Point Attack); // returns number of new orientations removed
    int emptyVector();
    const int getSize() const { return(m_size); }
    const Point getPosition() const { return(m_position); }
    Direction getDirZero() { if (m_orientation_array.size() == 1) { return(m_orientation_array[0].getdir()); } }
private:
    Point m_position;
    std::vector<OnCrossData> m_orientation_array; // possible orientation
    int m_size;
};

class Distribution
{
public:
    Distribution();
    Distribution(const Game& g, int shiplength);
    Distribution(const Game& g, int shiplength, std::vector<Point> Attacked);
    bool isValid(Point p) const { return((p.r >= 0) && (p.r < m_rows) && (p.c >= 0) && (p.c < m_cols)); }
    //void getMax(int& max, Point& Location);
    void reEvaluateDist(bool HitOrMiss, Point Attack, Point CenterOfCross);//, int& total_total_orientations);
    //const int getTotalOrientations() const { return(m_total_orientations); }
    const int getShipLength() const { return(m_shipLength); }
    const Orientations getPosOrientation(int r, int c) const { return(VariationShip[r][c]); }
private:
    Orientations VariationShip[MAXROWS][MAXCOLS];
    int m_shipLength;
    int m_rows;
    int m_cols;
    //int m_total_orientations;
};


class TotalDistribution
{
public:
    TotalDistribution(const Game& g);
    Point MostProbableLocation(const Game& g);
    void UpdateDist(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId, const Game& g);
    std::vector<Point>& getAttacked() { return(m_attacked); }
    bool isValid(Point p) const { return((p.r >= 0) && (p.r < m_rows) && (p.c >= 0) && (p.c < m_cols)); }
    void adjustRegisteredHits(int shipLength);
private:
    void storeProbInf(const Game& g, Distribution dist);
    int  m_probability[MAXROWS][MAXCOLS];
    std::vector<Distribution> DistGame;
    std::vector<int> m_shipId;
    std::vector<Point> m_attacked;
    std::vector<Point> m_hits;
    bool m_justDestroyedShipButThereAreHitSquares;
    int m_nShips;
    bool m_FoundCross;
    Point m_CrossCenter;
    int m_rows;
    int m_cols;
    //int m_total_total_orientations;
};
#endif // UTILITY_INCLUDED
