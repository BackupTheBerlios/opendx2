/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 2004                                        */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include "XmlPreferences.h"

#using <System.Xml.dll>
using namespace System;
using namespace System::Xml;
using namespace System::Runtime::InteropServices;


XmlPreferences* theXmlPreferences = 0;

void XmlPreferences::BuildTheXmlPreferences()
{
    if (theXmlPreferences == 0) 
	theXmlPreferences = new XmlPreferences();
}

XmlPreferences::XmlPreferences() {
	this->prefs = new XmlDocument();
	this->root = NULL;
	this->fileExisted = false;
}

XmlPreferences::~XmlPreferences() {

}

bool XmlPreferences::readPrefs(const char *filename) {
	System::String __gc *s = new System::String(filename);
	XmlTextReader* reader = new XmlTextReader(s);

	if(! reader) {
		return false;
	}

	try{
		this->prefs->Load(reader);
		this->fileExisted = true;
	} catch(System::Xml::XmlException *e) {
		ASSERT("Corrupted prefs file--try deleting");
	}

	reader->Close();

	this->root = this->prefs->SelectSingleNode(S"PREFS");
	if(!this->root) {
		XmlElement *elem = this->prefs->CreateElement(S"PREFS");
		this->prefs->AppendChild(elem);
		this->root = elem;
	}

	return this->fileExisted;
}

bool XmlPreferences::createPrefs() {
	ASSERT(this->prefs);
	try {
		XmlElement *elem = this->prefs->CreateElement(S"PREFS");
		this->prefs->AppendChild(elem);
		this->root = elem;
	} catch(Exception *e) {
		return false;
	}
	return true;
}



bool XmlPreferences::writePrefs(const char *filename) {
	this->fileExisted = false;

	// TODO: May want to remove non-persistent prefs. If so,
	// will need to traverse tree and remove them before 
	// trying to write file.

	try{
		this->prefs->Save(filename);
		this->fileExisted = true;
	} catch(System::Xml::XmlException *e) {
		// couldn't write file
	}
	return this->fileExisted;
}

bool XmlPreferences::getPref(const char *prefName, char *&value) {
	if(!this->prefs)
		return false;

	// Xml is in the form.
	//<PREF Name='UIRoot'><TYPE>string</TYPE><VALUE>/usr/local/dx</VALUE></PREF>
	//<PREF Name='wizard'><TYPE>bool</TYPE><VALUE>false</VALUE></PREF>

	System::String __gc *lookup = S"DXUIPREF[@Name='";
	lookup = System::String::Concat(lookup, new System::String(prefName));
	lookup = System::String::Concat(lookup, S"']");
	System::String __gc *val;
	try {
		XmlNode *n = this->root->SelectSingleNode(lookup);

		if(!n)
			return false;
		XmlNode *n2 = n->SelectSingleNode(S"VALUE");
		val = n2->InnerText;
	} catch (System::Xml::XmlException *e) {
		ASSERT("Corrupted prefs file--try deleting");
	}

	if(val->Length == 0) {
		value = NULL;
		return true;
	}

	value = new char[val->Length + 1];
	strncpy(value, 
		(const char*) (Marshal::StringToHGlobalAnsi(val)).ToPointer(),
		val->Length);
	value[val->Length] = '\0';

	return true;
}

bool XmlPreferences::getPref(const char *prefName, bool &value) {
	if(!this->prefs)
		return false;

	// Xml is in the form.
	//<PREF Name='UIRoot'><TYPE>string</TYPE><VALUE>/usr/local/dx</VALUE></PREF>
	//<PREF Name='wizard'><TYPE>bool</TYPE><VALUE>false</VALUE></PREF>

	System::String __gc *lookup = S"DXUIPREF[@Name='";
	lookup = System::String::Concat(lookup, new System::String(prefName));
	lookup = System::String::Concat(lookup, S"']");
	System::String __gc *val;
	try {
		XmlNode *n = this->root->SelectSingleNode(lookup);

		if(!n)
			return false;
		XmlNode *n2 = n->SelectSingleNode(S"VALUE");
		val = n2->InnerText;
	} catch (System::Xml::XmlException *e) {
		ASSERT("Corrupted prefs file--try deleting");
	}

	if(val->CompareTo(S"true") == 0)
		value = true;
	else
		value = false;

	return true;
}

bool XmlPreferences::getPref(const char *prefName, int &value) {
	if(!this->prefs)
		return false;

	// Xml is in the form.
	//<PREF Name='UIRoot'><TYPE>string</TYPE><VALUE>/usr/local/dx</VALUE></PREF>
	//<PREF Name='wizard'><TYPE>bool</TYPE><VALUE>false</VALUE></PREF>

	System::String __gc *lookup = S"DXUIPREF[@Name='";
	lookup = System::String::Concat(lookup, new System::String(prefName));
	lookup = System::String::Concat(lookup, S"']");
	System::String __gc *val;
	try {
		XmlNode *n = this->root->SelectSingleNode(lookup);

		if(!n)
			return false;
		XmlNode *n2 = n->SelectSingleNode(S"VALUE");
		val = n2->InnerText;
	} catch (System::Xml::XmlException *e) {
		ASSERT("Corrupted prefs file--try deleting");
	}

	value = Convert::ToInt32(val);

	return true;
}


bool XmlPreferences::getPref(const char* prefName, PrefType& type, char *&value) {
	if(!this->prefs)
		return false;

	// Xml is in the form.
	//<PREF Name='UIRoot'><TYPE>string</TYPE><VALUE>/usr/local/dx</VALUE></PREF>
	//<PREF Name='wizard'><TYPE>bool</TYPE><VALUE>false</VALUE></PREF>
	System::String __gc *lookup = S"DXUIPREF[@Name='";
	lookup = System::String::Concat(lookup, new System::String(prefName));
	lookup = System::String::Concat(lookup, S"']");

	System::String __gc *val, *typeS;
	try {
		XmlNode *n = this->root->SelectSingleNode(lookup);
		if(!n)
			return false;

		XmlNode *n2 = n->SelectSingleNode(S"VALUE");
		val = n2->InnerText;

		n2 = n->SelectSingleNode(S"TYPE");
		typeS = n2->InnerText;

	} catch (System::Xml::XmlException *e) {
		printf("Corrupted prefs file--try deleting\n");
		return false;
	}

	if(val->Length == 0) {
		value = NULL;
		return true;
	}

	value = new char[val->Length + 1];
	strncpy(value, 
		(const char*) (Marshal::StringToHGlobalAnsi(val)).ToPointer(),
		val->Length);
	value[val->Length] = '\0';

	if(typeS->CompareTo(S"bool") == 0)
		type = TypeBool;
	else if(typeS->CompareTo(S"int") == 0)
		type = TypeInt;
	else if(typeS->CompareTo(S"float") == 0)
		type = TypeFloat;
	else
		type = TypeString;

	return true;

}

bool XmlPreferences::setPref(const char *prefName, const char *value, bool persist) {
	if(!this->prefs)
		return false;
	System::String __gc *lookup = S"DXUIPREF[@Name='";
	lookup = System::String::Concat(lookup, new System::String(prefName));
	lookup = System::String::Concat(lookup, S"']");

	// First see if it exists. If so use replace.
	try {
		XmlNode *n = this->root->SelectSingleNode(lookup);
		if(n) {
			try{
				XmlElement *elem = this->prefs->CreateElement(S"DXUIPREF");
				elem->SetAttribute(S"Name", new System::String(prefName));
				XmlElement *val = this->prefs->CreateElement(S"VALUE");
				val->InnerText = new System::String(value);
				elem->AppendChild(val);
				XmlElement *persistent = this->prefs->CreateElement(S"PERSISTENT");
				if(persist)
					persistent->InnerText = S"true";
				else
					persistent->InnerText = S"false";
				elem->AppendChild(persistent);
				this->root->ReplaceChild(elem, n);
			} catch (System::Xml::XmlException *e) {
				return false;
			}
		} else
			try{
				XmlElement *elem = this->prefs->CreateElement(S"DXUIPREF");
				elem->SetAttribute(S"Name", new System::String(prefName));
				XmlElement *val = this->prefs->CreateElement(S"VALUE");
				val->InnerText = new System::String(value);
				elem->AppendChild(val);
				XmlElement *persistent = this->prefs->CreateElement(S"PERSISTENT");
				if(persist)
					persistent->InnerText = S"true";
				else
					persistent->InnerText = S"false";
				elem->AppendChild(persistent);
				this->root->AppendChild(elem);
			} catch (System::Xml::XmlException *e) {
				return false;
			}
	} catch (System::Xml::XmlException *e) {
		return false;
	}

	return true;

}

bool XmlPreferences::setPref(const char *prefName, PrefType type, const char *value, bool persist) {
	if(!this->prefs)
		return false;
	System::String __gc *lookup = S"DXUIPREF[@Name='";
	lookup = System::String::Concat(lookup, new System::String(prefName));
	lookup = System::String::Concat(lookup, S"']");

	System::String __gc *typeS;
	switch(type) {
		case TypeString:
			typeS = new System::String(S"string");
			break;
		case TypeInt:
			typeS = new System::String(S"int");
			break;
		case TypeBool:
			typeS = new System::String(S"bool");
			break;
		case TypeFloat:
			typeS = new System::String(S"float");
			break;
	}

	// First see if it exists. If so use replace.
	try {
		XmlNode *n = this->root->SelectSingleNode(lookup);
		if(n) {
			try{
				XmlElement *elem = this->prefs->CreateElement(S"DXUIPREF");
				elem->SetAttribute(S"Name", new System::String(prefName));
				XmlElement *val = this->prefs->CreateElement(S"VALUE");
				val->InnerText = new System::String(value);
				elem->AppendChild(val);
				XmlElement *tp = this->prefs->CreateElement(S"TYPE");
				tp->InnerText = typeS;
				elem->AppendChild(tp);
				XmlElement *persistent = this->prefs->CreateElement(S"PERSISTENT");
				if(persist)
					persistent->InnerText = S"true";
				else
					persistent->InnerText = S"false";
				elem->AppendChild(persistent);
				this->root->ReplaceChild(elem, n);
			} catch (System::Xml::XmlException *e) {
				return false;
			}
		} else
			try{
				XmlElement *elem = this->prefs->CreateElement(S"DXUIPREF");
				elem->SetAttribute(S"Name", new System::String(prefName));
				XmlElement *val = this->prefs->CreateElement(S"VALUE");
				val->InnerText = new System::String(value);
				elem->AppendChild(val);
				XmlElement *tp = this->prefs->CreateElement(S"TYPE");
				tp->InnerText = typeS;
				elem->AppendChild(tp);
				XmlElement *persistent = this->prefs->CreateElement(S"PERSISTENT");
				if(persist)
					persistent->InnerText = S"true";
				else
					persistent->InnerText = S"false";
				elem->AppendChild(persistent);
				this->root->AppendChild(elem);
			} catch (System::Xml::XmlException *e) {
				return false;
			}
	} catch (System::Xml::XmlException *e) {
		return false;
	}

	return true;

}

bool XmlPreferences::setDefault(const char *prefName, const char *value) {
	if(!this->prefs)
		return false;
	System::String __gc *lookup = S"DXUIPREF[@Name='";
	lookup = System::String::Concat(lookup, new System::String(prefName));
	lookup = System::String::Concat(lookup, S"']");

	// First see if it exists. If so just return true.
	try {
		XmlNode *n = this->root->SelectSingleNode(lookup);
		if(n) {
			return true;
		} else
			try{
				XmlElement *elem = this->prefs->CreateElement(S"DXUIPREF");
				elem->SetAttribute(S"Name", new System::String(prefName));
				XmlElement *val = this->prefs->CreateElement(S"VALUE");
				val->InnerText = new System::String(value);
				elem->AppendChild(val);
				XmlElement *persistent = this->prefs->CreateElement(S"PERSISTENT");
				persistent->InnerText = false;
				elem->AppendChild(persistent);
				this->root->AppendChild(elem);
			} catch (System::Xml::XmlException *e) {
				return false;
			}
	} catch (System::Xml::XmlException *e) {
		return false;
	}
	return true;
}

bool XmlPreferences::setDefault(const char *prefName, PrefType type, const char *value) {
	if(!this->prefs)
		return false;
	System::String __gc *lookup = S"DXUIPREF[@Name='";
	lookup = System::String::Concat(lookup, new System::String(prefName));
	lookup = System::String::Concat(lookup, S"']");

	System::String __gc *typeS;
	switch(type) {
		case TypeString:
			typeS = new System::String(S"string");
			break;
		case TypeInt:
			typeS = new System::String(S"int");
			break;
		case TypeBool:
			typeS = new System::String(S"bool");
			break;
		case TypeFloat:
			typeS = new System::String(S"float");
			break;
	}

	// First see if it exists. If so just return.
	try {
		XmlNode *n = this->root->SelectSingleNode(lookup);
		if(n) {
			return true;	
		} else
			try{
				XmlElement *elem = this->prefs->CreateElement(S"DXUIPREF");
				elem->SetAttribute(S"Name", new System::String(prefName));
				XmlElement *val = this->prefs->CreateElement(S"VALUE");
				val->InnerText = new System::String(value);
				elem->AppendChild(val);
				XmlElement *tp = this->prefs->CreateElement(S"TYPE");
				tp->InnerText = typeS;
				elem->AppendChild(tp);
				XmlElement *persistent = this->prefs->CreateElement(S"PERSISTENT");
				persistent->InnerText = S"false";
				elem->AppendChild(persistent);
				this->root->AppendChild(elem);
			} catch (System::Xml::XmlException *e) {
				return false;
			}
	} catch (System::Xml::XmlException *e) {
		return false;
	}

	return true;

}

