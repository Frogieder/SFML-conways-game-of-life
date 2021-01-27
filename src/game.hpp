enum class gridGenerators
{
    clean,
    random
};

class gameFunctions
{
private:
    bool active_a = true;
    int x_size;
    int y_size;
    bool *game_field_a;
    bool *game_field_b;
    void internalUpdateGrid(bool *source_game_field, bool *target_game_field);

public:
    int checkNeighbours(int x, int y, bool *game_field);
    bool *generateGrid(gridGenerators generator, int non_density = 3);
    bool *updateGrid();
    gameFunctions(int _x, int _y);
    ~gameFunctions();
};
