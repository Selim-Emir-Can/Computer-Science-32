#include"utility.h"
#include"Game.h"
#include<iostream>
#include<string>
#include<vector>

OnCrossData::OnCrossData()
	: m_point(0,0), m_length(0), m_dir(VERTICAL)
{}
OnCrossData::OnCrossData(Point point, int length, Direction dir)
	: m_point(point), m_length(length), m_dir(dir)
{}
Point OnCrossData::getpoint() const
{
	return(m_point);
}
int OnCrossData::getlength() const
{
	return(m_length);
}
Direction OnCrossData::getdir() const
{
	return(m_dir);
}

Ship::Ship(int length, char symbol, std::string name, int shipId)
	: m_name(name), m_symbol(symbol), m_length(length), m_shipId(shipId)
{}
std:: string Ship::getname() const
{
	return(m_name);
}
char Ship::getsymbol() const
{
	return(m_symbol);
}
int Ship::getlength() const
{
	return(m_length);
}
int Ship::getshipId() const
{
	return(m_shipId);
}

Orientations::Orientations()
	:m_size(0), m_position(0,0)
{}
Orientations::Orientations(int rows, int cols, int shiplength, Point point)
	: m_position(point), m_size(0)
{
	// VERTICAL ORIENTATATION
	Point temp1((point.r - (shiplength - 1)), point.c);
	while (temp1.r <= point.r)
	{
		if (isWholeShipValid(rows, cols, shiplength, temp1, VERTICAL))
		{
			OnCrossData ship(temp1, shiplength, VERTICAL);
			m_orientation_array.push_back(ship);
			m_size++;
		}
		temp1.r++;
	}
	// HORIZONTAL ORIENTATION
	Point temp2(point.r, (point.c - (shiplength - 1)));
	while (temp2.c <= point.c)
	{
		if (isWholeShipValid(rows, cols, shiplength, temp2, HORIZONTAL))
		{
			OnCrossData ship(temp2, shiplength, HORIZONTAL);
			m_orientation_array.push_back(ship);
			m_size++;
		}
		temp2.c++;
	}
}
Orientations::Orientations(int rows, int cols, int shiplength, Point point, std::vector<Point> Attacked)
	: m_position(point), m_size(0)
{
	// VERTICAL ORIENTATATION
	Point temp1((point.r - (shiplength - 1)), point.c);
	while (temp1.r <= point.r)
	{
		if (isWholeShipValid(rows, cols, shiplength, temp1, VERTICAL, Attacked))
		{
			OnCrossData ship(temp1, shiplength, VERTICAL);
			m_orientation_array.push_back(ship);
			m_size++;
		}
		temp1.r++;
	}
	// HORIZONTAL ORIENTATION
	Point temp2(point.r, (point.c - (shiplength - 1)));
	while (temp2.c <= point.c)
	{
		if (isWholeShipValid(rows, cols, shiplength, temp2, HORIZONTAL, Attacked))
		{
			OnCrossData ship(temp2, shiplength, HORIZONTAL);
			m_orientation_array.push_back(ship);
			m_size++;
		}
		temp2.c++;
	}
}
bool Orientations::isValid(Point p, std::vector<Point> Attacked) const
{
	for (unsigned int i = 0; i < Attacked.size(); i++)
	{
		if ((p.r == Attacked[i].r) && (p.c == Attacked[i].c))
		{
			return(false);
		}
	}

	return(true);
}
bool Orientations::isWholeShipValid(int rows, int cols, int shiplength, Point point, Direction Dir)
{
	if (Dir == VERTICAL)
	{
		for (int i = 0; i < shiplength; i++)
		{
			if (isValid(point, rows, cols) == false)
			{
				return(false);
			}
			point.r++;
		}
	}
	else
	{
		for (int i = 0; i < shiplength; i++)
		{
			if (isValid(point, rows, cols) == false)
			{
				return(false);
			}
			point.c++;
		}
	}
	return(true);
}
bool Orientations::isWholeShipValid(int rows, int cols, int shiplength, Point point, Direction Dir, std::vector<Point> Attacked)
{
	if (Dir == VERTICAL)
	{
		for (int i = 0; i < shiplength; i++)
		{
			if ((isValid(point, rows, cols) == false) || (isValid(point, Attacked) == false))
			{
				return(false);
			}
			point.r++;
		}
	}
	else
	{
		for (int i = 0; i < shiplength; i++)
		{
			if ((isValid(point, rows, cols) == false) || (isValid(point, Attacked) == false))
			{
				return(false);
			}
			point.c++;
		}
	}
	return(true);
}
bool Orientations::isPointOnShip(Point point, OnCrossData Ship)
{
	Point topOrLeft(Ship.getpoint());
	int ShipLength(Ship.getlength());
	if (Ship.getdir() == VERTICAL)
	{
		if ((point.c == topOrLeft.c) && (point.r >= topOrLeft.r) && (point.r <= (topOrLeft.r + (ShipLength - 1))))
		{
			return(true);
		}
	}
	else
	{
		if ((point.r == topOrLeft.r) && (point.c >= topOrLeft.c) && (point.c <= (topOrLeft.c + (ShipLength - 1))))
		{
			return(true);
		}
	}

	return(false);
}
int Orientations::reEvaluateOrientations(bool HitOrMiss, Point Attack)
{
	int removed = 0;
	if (HitOrMiss == true)	// we have a hit
	{
		for (int i = 0; i < m_size; i++)
		{
			if (isPointOnShip(Attack, m_orientation_array[i]))
			{
				;
			}
			else
			{
				std::vector<OnCrossData>::const_iterator p;
				p = m_orientation_array.begin();
				p = p + i;
				m_orientation_array.erase(p);
				m_size--;
				removed++;
			}
		}
	}
	else // we have a miss
	{
		for (int i = 0; i < m_size; i++)
		{
			if (isPointOnShip(Attack, m_orientation_array[i]))
			{
				std::vector<OnCrossData>::const_iterator p;
				p = m_orientation_array.begin();
				p = p + i;
				m_orientation_array.erase(p);
				m_size--;
				removed++;
			}
			else
			{
				;
			}
		}
	}
	return(removed);
}
int Orientations::emptyVector()
{
	int removed = m_size;
	m_orientation_array.clear();
	m_size = 0;	//change it back later
	return(removed);
}

Distribution::Distribution()
	: m_rows(0), m_cols(0), m_shipLength(0)//, m_total_orientations(0)
{}
Distribution::Distribution(const Game& g, int shiplength)
	:m_rows(g.rows()), m_cols(g.cols()), m_shipLength(shiplength)//, m_total_orientations(0)
{
	for (int r = 0; r < m_rows; r++)
	{
		for (int c = 0; c < m_cols; c++)
		{
			Point temp(r, c);
			VariationShip[r][c] = Orientations(m_rows, m_cols, shiplength, temp);
			//m_total_orientations = m_total_orientations + VariationShip[r][c].getSize();
		}
	}
}
Distribution::Distribution(const Game& g, int shiplength, std::vector<Point> Attacked)
	:m_rows(g.rows()), m_cols(g.cols()), m_shipLength(shiplength)//, m_total_orientations(0)
{
	for (int r = 0; r < m_rows; r++)
	{
		for (int c = 0; c < m_cols; c++)
		{
			Point temp(r, c);
			VariationShip[r][c] = Orientations(m_rows, m_cols, shiplength, temp, Attacked);
			//m_total_orientations = m_total_orientations + VariationShip[r][c].getSize();
		}
	}
}
/*void Distribution::getMax(int& max, Point& Location)	// the position that has the maximum number of orientations
{
	for (int r = 0; r < m_rows; r++)
	{
		for (int c = 0; c < m_cols; c++)
		{
			if (VariationShip[r][c].getSize() > max)
			{
				max = VariationShip[r][c].getSize();
				Location.r = r;
				Location.c = c;
			}
		}
	}
}*/
void Distribution::reEvaluateDist(bool HitOrMiss, Point Attack, Point CenterOfCross) //, int& total_total_orientations)
{
	if (HitOrMiss == true)
	{
		for (int r = 0; r < m_rows; r++)
		{
			for (int c = 0; c < m_cols; c++)
			{
				if ((Attack.c == c) && (Attack.r == r))
				{
					VariationShip[r][c].emptyVector();
				}
				else if (((CenterOfCross.c == c) && ((CenterOfCross.r - (m_shipLength - 1)) <= r) && ((CenterOfCross.r + (m_shipLength - 1)) >= r)) || ((CenterOfCross.r == r) && ((CenterOfCross.c - (m_shipLength - 1)) <= c) && ((CenterOfCross.c + (m_shipLength - 1)) >= c)))
				{
					VariationShip[r][c].reEvaluateOrientations(HitOrMiss, Attack);
				}
				else
				{
					VariationShip[r][c].emptyVector();
					//int rem = VariationShip[r][c].emptyVector();
					//m_total_orientations = m_total_orientations - rem;
					//total_total_orientations = total_total_orientations - rem;
				}
			}
		}
	}
	else
	{
		Point temp1((Attack.r - (m_shipLength - 1)), Attack.c);
		while (temp1.r <= (Attack.r + (m_shipLength - 1)))
		{
			if (isValid(temp1))
			{
				VariationShip[temp1.r][temp1.c].reEvaluateOrientations(HitOrMiss, Attack);
				//int rem = VariationShip[temp1.r][temp1.c].reEvaluateOrientations(HitOrMiss, Attack);
				//m_total_orientations = m_total_orientations - rem;
				//total_total_orientations = total_total_orientations - rem;
			}
			temp1.r++;
		}

		Point temp2(Attack.r, (Attack.c - (m_shipLength - 1)));
		while (temp2.c <= (Attack.c + (m_shipLength - 1)))
		{
			if (isValid(temp2))
			{
				VariationShip[temp2.r][temp2.c].reEvaluateOrientations(HitOrMiss, Attack);
				//int rem = VariationShip[temp2.r][temp2.c].reEvaluateOrientations(HitOrMiss, Attack);
				//m_total_orientations = m_total_orientations - rem;
				//total_total_orientations = total_total_orientations - rem;
			}
			temp2.c++;
		}
		
	}
	
}



void TotalDistribution::storeProbInf(const Game& g, Distribution dist)
{
	for (int r = 0; r < g.rows(); r++)
	{
		for (int c = 0; c < g.cols(); c++)
		{
			m_probability[r][c] = m_probability[r][c] + dist.getPosOrientation(r,c).getSize();
		}
	}
}
TotalDistribution::TotalDistribution(const Game& g)
	: m_nShips(g.nShips()), m_CrossCenter(-1,-1), m_FoundCross(false), m_justDestroyedShipButThereAreHitSquares(false), m_rows(g.rows()), m_cols(g.cols())//, m_total_total_orientations(0)
{
	for (int r = 0; r < g.rows(); r++)
	{
		for (int c = 0; c < g.cols(); c++)
		{
			m_probability[r][c] = 0;
		}
	}

	for (int i = 0; i < m_nShips; i++)
	{
		Distribution temp(g, g.shipLength(i));
		//m_total_total_orientations = m_total_total_orientations + temp.getTotalOrientations();
		DistGame.push_back(temp);
	}

	for (int i = 0; i < m_nShips; i++)
	{
		m_shipId.push_back(i);
		storeProbInf(g, DistGame[i]);
	}
}

void TotalDistribution::UpdateDist(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId, const Game& g) //RecordAttackResult
{
	if (validShot == true)
	{
		if (shotHit == true)
		{
			m_hits.push_back(p);
			if (m_FoundCross == false)
			{
				m_FoundCross = true;
				m_CrossCenter.r = p.r;
				m_CrossCenter.c = p.c;
			}
			if (shipDestroyed == true)
			{
				for (std::vector<int>::const_iterator p1 = m_shipId.begin(); p1 != m_shipId.end(); p1++)
				{
					if (*p1 == shipId)	// will execute every time
					{
						adjustRegisteredHits(g.shipLength(shipId));
						m_shipId.erase(p1);
						m_nShips--;
						break;
					}
				}

				if (m_hits.size() != 0)
				{
					m_justDestroyedShipButThereAreHitSquares = true;
				}
				// re initialize all the existing heatmaps
				DistGame.clear();
				for (int i = 0; i < m_nShips; i++)
				{
					Distribution temp(g, g.shipLength(m_shipId[i]), m_attacked);
					//m_total_total_orientations = m_total_total_orientations + temp.getTotalOrientations();
					DistGame.push_back(temp);
				}
				m_CrossCenter.r = -1;
				m_CrossCenter.c = -1;
				m_FoundCross = false;
			}
			else
			{
				for (int i = 0; i < m_nShips; i++)
				{
					DistGame[i].reEvaluateDist(true, p, m_CrossCenter);
				}
			}

		}
		else // missed shot
		{
			for (int i = 0; i < m_nShips; i++)
			{
				DistGame[i].reEvaluateDist(false, p, m_CrossCenter);
			}
		}
		for (int r = 0; r < g.rows(); r++)
		{
			for (int c = 0; c < g.cols(); c++)
			{
				m_probability[r][c] = 0;
			}
		}
		for (int i = 0; i < m_nShips; i++)
		{
			storeProbInf(g, DistGame[i]);
		}
	}
}
Point TotalDistribution::MostProbableLocation(const Game& g)	// Recommend Attack
{
	if ((m_hits.size() != 0) && (m_justDestroyedShipButThereAreHitSquares == true))
	{
		Point temp(0, 0);
		bool success = false;
		bool broke = false;
		int i = 0;
		while (success == false)
		{
			i++;
			if (i >= 50)
			{
				
				if (m_hits.size() != 0)
				{
					std::vector<Point>::const_iterator p = m_hits.begin();
					m_hits.erase(p);
				}
				else
				{
					m_justDestroyedShipButThereAreHitSquares = false; // added this to fix error
					Point temp(randInt(g.rows()), randInt(g.cols()));
					return(temp);
				}
				/*
				m_justDestroyedShipButThereAreHitSquares = false; // added this to fix error

				Point temp(randInt(g.rows()), randInt(g.cols()));
				while (success == false)
				{
					for (unsigned int i = 0; i < m_attacked.size(); i++)
					{
						if ((m_attacked[i].r == temp.r) && (m_attacked[i].c == temp.c))
						{
							break;
						}
					}

					if (i == m_attacked.size())
					{
						return(temp);
					}
					else
					{
						temp.r = randInt(g.rows());
						temp.c = randInt(g.cols());
					}
					
				}
				return(temp);
				*/
			}
			if (m_hits.size() != 0)
			{
				if (randInt(2) == 0)
				{
					if (randInt(2) == 0)
					{
						temp.r = (m_hits[0].r + randInt(4) + 1);
						temp.c = m_hits[0].c;
						if (isValid(temp) == true)
						{
							for (unsigned int i = 0; i < m_attacked.size(); i++)
							{
								if ((m_attacked[i].r == temp.r) && (m_attacked[i].c == temp.c))
								{
									broke = true;
									break;
								}
							}

							if (broke == false)
							{
								m_attacked.push_back(temp);
								return(temp);
							}
							else
							{
								broke = false;
							}
						}
					}
					else
					{
						temp.r = (m_hits[0].r - randInt(4) - 1);
						temp.c = m_hits[0].c;
						if (isValid(temp) == true)
						{
							for (unsigned int i = 0; i < m_attacked.size(); i++)
							{
								if ((m_attacked[i].r == temp.r) && (m_attacked[i].c == temp.c))
								{
									broke = true;
									break;
								}
							}

							if (broke == false)
							{
								m_attacked.push_back(temp);
								return(temp);
							}
							else
							{
								broke = false;
							}
						}
					}
				}
				else
				{
					if (randInt(2) == 0)
					{
						temp.r = m_hits[0].r;
						temp.c = (m_hits[0].c - randInt(4) - 1);
						if (isValid(temp) == true)
						{
							for (unsigned int i = 0; i < m_attacked.size(); i++)
							{
								if ((m_attacked[i].r == temp.r) && (m_attacked[i].c == temp.c))
								{
									broke = true;
									break;
								}
							}

							if (broke == false)
							{
								m_attacked.push_back(temp);
								return(temp);
							}
							else
							{
								broke = false;
							}
						}
					}
					else
					{
						temp.r = m_hits[0].r;
						temp.c = (m_hits[0].c + randInt(4) + 1);
						if (isValid(temp) == true)
						{
							for (unsigned int i = 0; i < m_attacked.size(); i++)
							{
								if ((m_attacked[i].r == temp.r) && (m_attacked[i].c == temp.c))
								{
									broke = true;
									break;
								}
							}

							if (broke == false)
							{
								m_attacked.push_back(temp);
								return(temp);
							}
							else
							{
								broke = false;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		m_justDestroyedShipButThereAreHitSquares = false;
		int max = 0;
		Point Max(0, 0);
		for (int r = 0; r < g.rows(); r++)
		{
			//std::cout << std::endl;
			for (int c = 0; c < g.cols(); c++)
			{
				//std::cout << m_probability[r][c] << " ";
				if (max < m_probability[r][c])
				{
					max = m_probability[r][c];
					Max.r = r;
					Max.c = c;
				}
			}
		}

		if (max == 0)
		{
			m_justDestroyedShipButThereAreHitSquares = true;
		}
		m_attacked.push_back(Max);
		return(Max);
	}
	Point temp(randInt(g.rows()), randInt(g.cols()));
	return(temp);
}

void TotalDistribution::adjustRegisteredHits(int shipLength)
{
	unsigned int size = m_hits.size();
	if (size != 0)
	{
		if (m_hits.size() != 0)
		{
			if (size == shipLength)
			{
				m_hits.clear();
			}
			else
			{
				std::vector<Point> erase;
				Point lasthit = m_hits[(size - 1)];
				int found = 0;
				for (int i = 0; i < shipLength; i++)
				{
					Point temp((lasthit.r - i), lasthit.c);
					for (unsigned int k = 0; k < m_hits.size(); k++)
					{
						if ((m_hits[k].r == temp.r) && (m_hits[k].c == temp.c))
						{
							erase.push_back(m_hits[k]);
							found++;
						}
					}
				}

				if (found == shipLength)
				{
					for (unsigned int i = 0; i < erase.size(); i++)
					{
						for (unsigned int k = 0; k < m_hits.size(); k++)
						{
							if ((m_hits[k].r == erase[i].r) && (m_hits[k].c == erase[i].c))
							{
								std::vector<Point>::const_iterator p = m_hits.begin();
								p = p + k;
								m_hits.erase(p);
								break;
							}
						}
					}
				}
				else
				{
					found = 0;
					erase.clear();
					for (int i = 0; i < shipLength; i++)
					{
						Point temp((lasthit.r + i), lasthit.c);
						for (unsigned int k = 0; k < m_hits.size(); k++)
						{
							if ((m_hits[k].r == temp.r) && (m_hits[k].c == temp.c))
							{
								erase.push_back(m_hits[k]);
								found++;
							}
						}
					}

					if (found == shipLength)
					{
						for (unsigned int i = 0; i < erase.size(); i++)
						{
							for (unsigned int k = 0; k < m_hits.size(); k++)
							{
								if ((m_hits[k].r == erase[i].r) && (m_hits[k].c == erase[i].c))
								{
									std::vector<Point>::const_iterator p = m_hits.begin();
									p = p + k;
									m_hits.erase(p);
									break;
								}
							}
						}
					}
					else
					{
						found = 0;
						erase.clear();
						for (int i = 0; i < shipLength; i++)
						{
							Point temp(lasthit.r, (lasthit.c + i));
							for (unsigned int k = 0; k < m_hits.size(); k++)
							{
								if ((m_hits[k].r == temp.r) && (m_hits[k].c == temp.c))
								{
									erase.push_back(m_hits[k]);
									found++;
								}
							}
						}

						if (found == shipLength)
						{
							for (unsigned int i = 0; i < erase.size(); i++)
							{
								for (unsigned int k = 0; k < m_hits.size(); k++)
								{
									if ((m_hits[k].r == erase[i].r) && (m_hits[k].c == erase[i].c))
									{
										std::vector<Point>::const_iterator p = m_hits.begin();
										p = p + k;
										m_hits.erase(p);
										break;
									}
								}
							}
						}
						else
						{
							found = 0;
							erase.clear();
							for (int i = 0; i < shipLength; i++)
							{
								Point temp(lasthit.r, (lasthit.c - i));
								for (unsigned int k = 0; k < m_hits.size(); k++)
								{
									if ((m_hits[k].r == temp.r) && (m_hits[k].c == temp.c))
									{
										erase.push_back(m_hits[k]);
										found++;
									}
								}
							}

							if (found == shipLength)
							{
								for (unsigned int i = 0; i < erase.size(); i++)
								{
									for (unsigned int k = 0; k < m_hits.size(); k++)
									{
										if ((m_hits[k].r == erase[i].r) && (m_hits[k].c == erase[i].c))
										{
											std::vector<Point>::const_iterator p = m_hits.begin();
											p = p + k;
											m_hits.erase(p);
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}





