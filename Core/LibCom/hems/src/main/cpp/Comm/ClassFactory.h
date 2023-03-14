#pragma once
#include <map>
#include <string>

//#define NoSupportCpp11

#ifdef NoSupportCpp11

template<class OutClass, typename TagClass>
class ClassFactory
{
public:
	typedef OutClass* (*CreateObject)(void);

	static ClassFactory& Instance() {
		static ClassFactory _classFactory;
		return _classFactory;
	}

	OutClass* Create(const TagClass& tag) {
		typename std::map<TagClass, CreateObject>::iterator ite = m_mapClass.find(tag);
		if (ite != m_mapClass.end())
		{
			return ite->second();
		}
		return NULL;
	}

	void Release(OutClass* &obj) {
		delete obj;
		obj = nullptr;
	}

	void  Register(const TagClass& tag, CreateObject method) {
		m_mapClass.insert(std::pair<TagClass, CreateObject>(tag, method));
	}
protected:
	ClassFactory(void) {}
	virtual ~ClassFactory(void) {}
private:
	std::map<TagClass, CreateObject> m_mapClass;
};

template<class OutClass, class NewClass, typename TagClass>
class Reflection
{
public:
	Reflection(TagClass tag) {
		ClassFactory<OutClass, TagClass>::Instance().Register(tag, Create);
	}
	virtual ~Reflection() {}

	static OutClass* Create() {
		return new NewClass();
	}

};

#else


template<				// �����࣬��c11֧�֣�֧�ִ������Ĺ��캯��
	class OutClass,		// ��Ҫ������������
	typename TagClass,  // ��������Ҫ�� ��־
	class... Types		// ��Ҫ���ɵ���Ĺ��캯�� ����Ҫ�Ĳ��� c11֧��
>    

class ClassFactory
{
public:
	typedef OutClass* (*CreateObject1)(Types... args);

	static ClassFactory& Instance() {
		 static ClassFactory _classFactory;
		return _classFactory;
	}

	OutClass* Create(const TagClass& tag, Types... args) {
		typename std::map<TagClass, CreateObject1>::iterator ite = m_mapClass.find(tag);
		if (ite != m_mapClass.end())
		{
			return ite->second(args...);
		}
		return NULL;
	}

	void Release(OutClass* &obj) {
		delete obj;
		obj = nullptr;
	}

	/**
	 * \brief	Registers this object
	 *
	 * \param	tag   	The tag
	 * \param	method	The method
	 * \attention	��˵��
	 * \exception	���쳣
	 * \author	������ A15145
	 * \date	2021/7/5
	 */
	void  Register(const TagClass& tag, CreateObject1 method) {
		m_mapClass.insert(std::pair<TagClass, CreateObject1>(tag, method));
	}

	virtual ~ClassFactory(void) {
	}
protected:
	ClassFactory(void) {
	}
	
private:
	std::map<TagClass, CreateObject1> m_mapClass;
};


template<				// �����࣬��c11֧�֣�֧�ִ������Ĺ��캯��
	class OutClass,		// ��Ҫ������������ ����NewClass ��ͬ
	class NewClass,		// �����������ɵ���
	typename TagClass,  // ����������Ҫ�ı�ǩ
	class... Types		// ��Ҫ���ɵ���Ĺ��캯�� ����Ҫ�Ĳ��� c11֧��
>
class Reflection
{
public:
	Reflection(TagClass tag) {
		ClassFactory<OutClass, TagClass, Types...>::Instance().Register(tag, Create);
	}
	virtual ~Reflection() {
		//int nTest = 0;
		//nTest = 3;
	}

	static OutClass* Create(Types... args) {
		return new NewClass(args...);
	}

	static void Release(OutClass* &obj) {
		delete obj;
		obj = nullptr;
	}
};

#endif