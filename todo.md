
# UI
* attribute UI has anchoring
* attribute Pos has offset with flags (bottom, center, left, right) +/- deltas.

# World
* AttributeCamera should move itself, and has target SceneNode
* Each attribute pos has a ptr to its parents attrPos for making the world position



Walk around

Application ->
    onPickPlant: plant
        add plant to inventory

Invetory is hidden by default
    hit inventory button to open it
    and disable player input
    show all the ingredients
    show what properties they have


```



class Ingredient {

}


class Inventory {
public:

private:
    std::list<Ingredient> _ingredients;
    std::list<Reagent> _reagents;
    std::list<Potion> _potions;
};
```
