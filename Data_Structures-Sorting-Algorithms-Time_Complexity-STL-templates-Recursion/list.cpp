
void listAll(const Domain* d, string path) // two-parameter overload
{
    if (d->subdomains().size() == 0)
    {
        if (path == "")
        {
            path = d->label();
            std::cout << path << std::endl;
            return;
        }
        else if (d->label() != path) // if (d->label() != root domain name)
        {
            path = d->label() + path;
            std::cout << path << std::endl;
            return;
        }
        else
        {
            std::cout << path << std::endl;
            return;
        }
    }

    if (path == "")
    {
        path = d->label();
    }
    else if (d->label() != path) // if (d->label() != root domain name)
    {
        path = d->label() + path;
    }


    for (unsigned int i = 0; i < d->subdomains().size(); i++)
    {
        if (path == "")
        {
            listAll(d->subdomains()[i], path);
        }
        else
        {
            listAll(d->subdomains()[i], ("." + path));
        }
    }


    //You will write this code.
}
