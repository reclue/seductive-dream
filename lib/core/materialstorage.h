#ifndef MATERIALSTORAGE_H
#define MATERIALSTORAGE_H

#include "icanbeeverywhere.h"
#include "collectionof.h"
#include "material.h"


class MaterialStorage final :
        public ICanBeEverywhere
{
private:
    CollectionOf<Material> m_materials;

public:
    MaterialStorage();
    ~MaterialStorage();

public:
    MaterialStorage(const MaterialStorage&) = delete;
    MaterialStorage(MaterialStorage&&) noexcept = delete;
    MaterialStorage& operator=(const MaterialStorage&) = delete;
    MaterialStorage& operator=(MaterialStorage&&) noexcept = delete;

public:
    CollectionOf<Material>& GetMaterials();
    const CollectionOf<Material>& GetMaterials() const;
};

#endif // MATERIALSTORAGE_H
