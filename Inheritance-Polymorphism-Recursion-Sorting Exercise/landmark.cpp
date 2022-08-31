class Landmark;
class Hotel;
class Restaurant;
class Hospital;

// can't declare anymore classes
//Other than constructors and destructors (which can't be const), all member functions must be const member functions.

class Landmark
{
public:                                      //can't have a default constructor
    Landmark(std::string name);              // I decided that the useful parameter is the name  
    virtual ~Landmark();
    const std::string name() const;
    virtual const std::string icon() const = 0;
    virtual const std::string color() const;
    
private:
    std::string m_name;
};
Landmark::Landmark(std::string name)
    :m_name(name)
{}
Landmark::~Landmark()   // this is the same as the default destructor
{}
const std::string Landmark::name() const
{
    return(m_name);
}
const std::string Landmark::color() const
{
    return("yellow");
}





class Hotel : public Landmark   // maybe make others inherit from a hotel??
{
public:
    Hotel(std::string name);
    ~Hotel();
    virtual const std::string icon()  const;
};
Hotel::Hotel(std::string name)
    :Landmark(name)
{}
Hotel::~Hotel()
{
    std::cout << "Destroying the hotel " << this->name() << ".\n";
}
std::string const Hotel::icon() const
{
    return("bed");
}





class Restaurant : public Landmark
{
public:
    Restaurant(std::string name, int capactiy);
    ~Restaurant();
    virtual const std::string icon()  const;
private:
    int m_capacity;
};
Restaurant::Restaurant(std::string name, int capacity) //Can only construct if capacity > 0
    :Landmark(name), m_capacity(capacity)
{}
Restaurant::~Restaurant()
{
    std::cout << "Destroying the restaurant " << this->name() << ".\n";
}
const std::string Restaurant::icon() const  // does not check if m_capacity <= 0
{
    if (m_capacity < 40)
    {
        return("small knife/fork");
    }
    else // (m_capacity >= 40)
    {
        return("large knife/fork");
    }
}





class Hospital : public Landmark
{
public:
    Hospital(std::string name);
    ~Hospital();
    const std::string icon() const;
    const std::string color() const;
};
Hospital::Hospital(std::string name)
    :Landmark(name)
{}
Hospital::~Hospital()
{
    std::cout << "Destroying the hospital " << this->name() << ".\n";
}
const std::string Hospital::icon() const
{
    return("H");
}
const std::string Hospital::color() const
{
    return("blue");
}


// new Landmark("La Picadura del Oso") must produce a compilation error.
///////// this suggests that I make landmark a an abstract class

//No two functions with non-empty bodies may have the same implementation, or implementations that have the same effect for a caller.
//////// this suggest that I need to define distinct empty body functions for all classes if they need a version of that function

//No implementation of a name() function may explicitly call any other function.
//No class may have a data member whose value is identical for every object of a particular class type.
//All data members must be declared private. You may declare member functions public or private. 