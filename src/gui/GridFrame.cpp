#include "GridFrame.h"
#include <fmt/format.h>

template<typename T>
void swap(T &t1, T &t2) noexcept {
    T temp = std::move(t1);
    t1 = std::move(t2);
    t2 = std::move(temp);
}

GridFrame::~GridFrame() {
    for (GridObject &object: m_objects) {
        object.placeable = nullptr;
    }
}

void GridFrame::setGrid(const int &rows, const int &columns) {
    if (m_rows == 0 || m_columns == 0) {
        m_rows = rows;
        m_columns = columns;
        return;
    }
    if (rows < m_rows || columns < m_columns) {
        fmt::println("Grid resize illegal rows: {}, columns: {}", rows - m_rows, columns - m_columns);
        return;
    }
    for (int row = m_rows - 1; row > 0; --row) {
        for (int column = m_columns - 1; column > 0; --column) {
            const int &index = row * m_columns + column;
            const int &new_index = row * rows + column;
            swap(m_objects[index], m_objects[new_index]);
        }
    }
    m_rows = rows;
    m_columns = columns;
}

void GridFrame::setRowHeight(const int &row, const int &height) {
    m_row_heights[row] = height;
}

void GridFrame::setColumnWidth(const int &column, const int &width) {
    m_column_widths[column] = width;
}

void GridFrame::draw(sf::RenderWindow &window) {
    for (const GridObject &object: m_objects) {
        object.placeable->draw(window);
    }
}

void GridFrame::setSize(const int &width, const int &height) {
    if (m_rows == 0 || m_columns == 0) return;
}

void GridFrame::setPosition(const int &x, const int &y) {
}

void GridFrame::setPosize(const int &x, const int &y, const int &width, const int &height) {
}
