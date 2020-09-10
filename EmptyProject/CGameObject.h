#pragma once
class CComponent;
class CTransform;
class CGameObject
{
public:
	CGameObject();
	~CGameObject();

public:
	string m_Name;
	Tag m_Tag;
	CTransform * tf;
public:
	CGameObject * m_pParent = nullptr;
	vector<CGameObject*>  m_pChild;
public:
	list <CComponent*> m_listComponent;

	template<class T>
	T * gc()
	{
		for (auto iter : m_listComponent)
		{
			T* Comp = dynamic_cast<T*>(iter);
			if (Comp != nullptr)
				return Comp;
		}
		return nullptr;
	}

	template<class T>
	T * ac()
	{
		if (gc<T>()) return gc<T>();

		CComponent * pComponent = new T();

		pComponent->go = this;

		pComponent->sa = new CScheduleAdmin():

		m_listComponent.push_back(pComponent);
	}
public:
};

