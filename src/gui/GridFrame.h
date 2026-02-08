#ifndef LEARNINGSFML_GRIDFRAME_H
#define LEARNINGSFML_GRIDFRAME_H
#include <array>

#include "../gui/interfaces/IDrawables.h"

struct GridObject {
    std::unique_ptr<IPlaceable> placeable = nullptr;
    int column_span = -1;
    int row_span = -1;
    int column = -1;
    int row = -1;
};

class GridFrame : public IPlaceable {
public:
    static constexpr int MAX_GRID_SIZE = 20;
    static constexpr int MAX_GRID_ARRAY = MAX_GRID_SIZE * MAX_GRID_SIZE;

private:
    std::array<int, MAX_GRID_SIZE> m_row_heights = {};
    std::array<int, MAX_GRID_SIZE> m_column_widths = {};
    std::array<GridObject, MAX_GRID_ARRAY> m_objects = {};

protected:
    int m_x = 0;
    int m_y = 0;
    int m_width = 0;
    int m_height = 0;

    int m_rows = 0;
    int m_columns = 0;
    float m_row_height = 0;
    float m_column_width = 0;

public:
    ~GridFrame() override;

    void setGrid(const int &rows, const int &columns);

private:
    void setRowHeight(const int &row, const int &height);

    void setColumnWidth(const int &column, const int &width);

public:
    void draw(sf::RenderWindow &window) const override;

    void setSize(const int &width, const int &height) override;

    void setPosition(const int &x, const int &y) override;

    void setPosize(const int &x, const int &y, const int &width, const int &height) override;
};


#endif //LEARNINGSFML_GRIDFRAME_H
