#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include <iostream>
#include <string>
#include <list>

using namespace std;
 
class Element
{
	private:
		
		string tagName;
		list<string> attrList;
		string innerHTML;
	
	public:
		
		Element(void);
		Element(string, list<string>, string);
		Element(const Element&);
		string getTagName(void);
		list<string> attributeList(void);
		string getInnerHTML(void);
		void setTagName(string);
		void setAttributeList(list<string>);
		void setInnerHTML(string);
		Element& operator= (const Element &nodo);
};

/* --------------------------------------------------------- */
 
Element::Element(void)
{
	tagName = " ";
	attrList.clear();
	innerHTML = " ";
}
 
Element::Element(string tag, list<string> attr, string inner)
{
	tagName = tag;
	attrList = attr;
	innerHTML = inner;
}
 
Element::Element(const Element &e)
{
	tagName = e.tagName;
	attrList = e.attrList;
	innerHTML = e.innerHTML;
}
 
string Element::getTagName(void)
{
	return tagName;
}

list<string> Element::attributeList(void)
{
	return attrList;
}
 
string Element::getInnerHTML(void)
{
	return innerHTML;
}

void Element::setTagName(string tag)
{
	tagName = tag;
}
 
void Element::setAttributeList(list<string> l)
{
	attrList = l;
}

 
void Element::setInnerHTML(string inner)
{
	innerHTML = inner;
}

Element& Element::operator= (const Element &e)
{
	this->tagName = e.tagName;
	this->attrList = e.attrList;
	this->innerHTML = e.innerHTML;	
	return *this;
}

#endif
