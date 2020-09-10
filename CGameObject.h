#pragma once
class CComponent;
class CTransform;
class CScheduleAdmin;
class CGameObject
{
public:
	CGameObject();
	~CGameObject();

public:
	bool m_bEnable = true;

	string m_Name;
	Tag m_Tag;
	CTransform * tf;
	bool m_bDestroy = false;
public:
	CGameObject * m_pParent = nullptr;
	list<CGameObject*>  m_listChild;
	void Destroy();

	void AddChild(CGameObject * _Child)
	{
		m_listChild.push_back(_Child);
		_Child->m_pParent = this;
	}
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

		pComponent->tf = tf;

		pComponent->Awake();

		m_listComponent.push_back(pComponent);

		return (T*)pComponent;
	}
public:
};

