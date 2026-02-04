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
    if (rows > MAX_GRID_SIZE || columns > MAX_GRID_SIZE) {
        fmt::println("Grid resize too big rows: {}, columns: {}", rows, columns);
        return;
    }
    if (m_rows == 0 || m_columns == 0) {
        m_rows = rows;
        m_columns = columns;
        return;
    }
    if (rows < m_rows || columns < m_columns) {
        fmt::println("Grid resize smaller rows: {}, columns: {}", rows - m_rows, columns - m_columns);
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
    const int &grid_size = m_rows * m_columns;
    for (int i = 0; i < grid_size; ++i) {
        GridObject &object = m_objects[i];
        if (object.placeable == nullptr) continue;
        object.placeable->draw(window);
    }
}

void GridFrame::setSize(const int &width, const int &height) {
    m_width = width, m_height = height;
    if (m_rows == 0 || m_columns == 0) return;
    const int &width_distribution = m_width / m_rows;
    const int &height_distribution = m_height / m_columns;
    const int &grid_size = m_rows * m_columns;
    for (int i = 0; i < grid_size; ++i) {
        GridObject &object = m_objects[i];
        if (object.placeable == nullptr) continue;
        object.placeable->setPosition(m_x + object.column * width_distribution, m_y + object.row * height_distribution);
        object.placeable->setSize(object.column_span * width_distribution, object.row_span * height_distribution);
    }
}

void GridFrame::setPosition(const int &x, const int &y) {
    m_x = x, m_y = y;
    if (m_rows == 0 || m_columns == 0) return;
    const int &width_distribution = m_width / m_rows;
    const int &height_distribution = m_height / m_columns;
    const int &grid_size = m_rows * m_columns;
    for (int i = 0; i < grid_size; ++i) {
        GridObject &object = m_objects[i];
        if (object.placeable == nullptr) continue;
        object.placeable->setPosition(m_x + object.column * width_distribution, m_y + object.row * height_distribution);
    }
}

void GridFrame::setPosize(const int &x, const int &y, const int &width, const int &height) {
    m_x = x, m_y = y, m_width = width, m_height = height;
    if (m_rows == 0 || m_columns == 0) return;
    const int &width_distribution = width / m_rows;
    const int &height_distribution = height / m_columns;
    const int &grid_size = m_rows * m_columns;
    for (int i = 0; i < grid_size; ++i) {
        GridObject &object = m_objects[i];
        if (object.placeable == nullptr) continue;
        object.placeable->setPosition(m_x + object.column * width_distribution, m_y + object.row * height_distribution);
        object.placeable->setSize(object.column_span * width_distribution, object.row_span * height_distribution);
    }
}
