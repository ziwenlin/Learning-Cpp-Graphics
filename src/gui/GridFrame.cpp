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

void GridFrame::clear() {
    const int &grid_size = m_rows * m_columns;
    for (int i = 0; i < grid_size; ++i) {
        GridObject &object = m_objects[i];
        object.placeable = nullptr;
    }
    m_rows = 0, m_columns = 0, m_width = 0, m_height = 0;
}

void GridFrame::addElement(IPlaceable *element, const int &row, const int &column, const int &row_span, const int &column_span) {
    if (row > m_rows || column > m_columns) return;
    const int &index = row * m_columns + column;
    m_objects[index].placeable = element;
    setElementSize(index, row_span, column_span);
    setElementPosition(index, row, column);
}

float GridFrame::getRowHeight(const int &row) const {
    if (const int &height = m_row_heights[row]; height > 0) {
        return static_cast<float>(height);
    }
    return m_row_height;
}

float GridFrame::getColumnWidth(const int &column) const {
    if (const int &width = m_column_widths[column]; width > 0) {
        return static_cast<float>(width);
    }
    return m_column_width;
}

void GridFrame::setGrid(const int &rows, const int &columns) {
    if (rows > MAX_GRID_SIZE || columns > MAX_GRID_SIZE) {
        fmt::println("Grid resize too big rows: {}, columns: {}", rows, columns);
        return;
    }
    if (m_rows == 0 || m_columns == 0) {
        m_rows = rows;
        m_columns = columns;
        processColumWidths();
        processRowHeights();
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
    processColumWidths();
    processRowHeights();
}

void GridFrame::setElementSize(const int &index, const int &row_span, const int &column_span) {
    GridObject &object = m_objects[index];
    object.column_span = column_span;
    object.row_span = row_span;
    float total_height = 0;
    for (int row_index = 0; row_index < row_span; row_index++) {
        total_height += getRowHeight(row_index + row_span);
    }
    float total_width = 0;
    for (int column_index = 0; column_index < column_span; column_index++) {
        total_width += getColumnWidth(column_index + column_span);
    }
    object.placeable->setSize(static_cast<int>(total_width), static_cast<int>(total_height));
}

void GridFrame::setElementPosition(const int &index, const int &row, const int &column) {
    GridObject &object = m_objects[index];
    object.column = column;
    object.row = row;
    float total_x = 0;
    for (int column_index = 0; column_index < column; column_index++) {
        total_x += getColumnWidth(column_index);
    }
    float total_y = 0;
    for (int row_index = 0; row_index < row; row_index++) {
        total_y += getRowHeight(row_index);
    }
    object.placeable->setPosition(static_cast<int>(total_x), static_cast<int>(total_y));
}

void GridFrame::processRowHeights() {
    if (m_rows == 0 || m_height == 0) return;
    int total = 0, total_count = 0;
    for (int index = 0; index < m_rows; index++) {
        const int &row_height = m_row_heights[index];
        if (row_height > 0) {
            total_count++;
        }
        total += row_height;
    }
    if (total_count < m_rows) {
        m_row_height = static_cast<float>(m_height - total) / static_cast<float>(m_rows - total_count);
    } else {
        m_row_height = 0.f;
    }
}

void GridFrame::processColumWidths() {
    if (m_columns == 0 || m_width == 0) return;
    int total = 0, total_count = 0;
    for (int index = 0; index < m_columns; ++index) {
        const int &column_width = m_column_widths[index];
        if (column_width > 0) {
            total_count++;
        }
        total += column_width;
    }
    if (total_count < m_columns) {
        m_column_width = static_cast<float>(m_width - total) / static_cast<float>(m_columns - total_count);
    } else {
        m_column_width = 0.f;
    }
}

void GridFrame::setRowHeight(const int &row, const int &height) {
    m_row_heights[row] = height;
    processRowHeights();
}

void GridFrame::setColumnWidth(const int &column, const int &width) {
    m_column_widths[column] = width;
    processColumWidths();
}

void GridFrame::update(const SmartMouse &mouse) {
    const int &grid_size = m_rows * m_columns;
    for (int i = 0; i < grid_size; ++i) {
        const GridObject &object = m_objects[i];
        if (object.placeable == nullptr) continue;
        if (IClickable *clickable = dynamic_cast<IClickable *>(object.placeable); clickable != nullptr) {
            clickable->update(mouse);
        }
    }
}

void GridFrame::draw(sf::RenderWindow &window) const {
    const int &grid_size = m_rows * m_columns;
    for (int i = 0; i < grid_size; ++i) {
        const GridObject &object = m_objects[i];
        if (object.placeable == nullptr) continue;
        object.placeable->draw(window);
    }
}

void GridFrame::setSize(const int &width, const int &height) {
    m_width = width, m_height = height;
    if (m_rows == 0 || m_columns == 0) return;
    processColumWidths();
    processRowHeights();
    const int &width_distribution = m_width / m_rows;
    const int &height_distribution = m_height / m_columns;
    const int &grid_size = m_rows * m_columns;
    for (int i = 0; i < grid_size; ++i) {
        const GridObject &object = m_objects[i];
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
        const GridObject &object = m_objects[i];
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
        const GridObject &object = m_objects[i];
        if (object.placeable == nullptr) continue;
        object.placeable->setPosition(m_x + object.column * width_distribution, m_y + object.row * height_distribution);
        object.placeable->setSize(object.column_span * width_distribution, object.row_span * height_distribution);
    }
}
