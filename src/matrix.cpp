#include "matrix.h"
#include <iostream>
#include <tuple>
#include <random>
#include <chrono>
Matrix::Matrix()
{
    this->head = nullptr;
    this->head_vertical = nullptr;
    this->list_size = 0;
    this->max_row_index = 0;
    this->max_col_index = 0;
    this->precedence_factor = 0;
}
Matrix::Matrix(std::string file)
{
    this->head = nullptr;
    this->head_vertical = nullptr;
    this->list_size = 0;
    this->max_row_index = 0;
    this->max_col_index = 0;
    this->precedence_factor = 0;
    readFile(file);
}
void Matrix::setMaxRow(unsigned int row)
{
    this->max_row_index = row;
}
void Matrix::setMaxCol(unsigned int col)
{
    this->max_col_index = col;
}
void Matrix::addElement(int data, unsigned int row, unsigned int col)
{
    if (row > max_row_index)
    {
        setMaxRow(row);
    }
    if (col > max_col_index)
    {
        setMaxCol(col);
    }
    this->precedence_factor = std::max(this->max_row_index, this->max_col_index) + 1;
    Node* new_node = new Node(data, row, col, nullptr, nullptr);
    Node* curr = this->head;
    if (this->list_size == 0)
    {
        this->head = new_node;
        this->list_size++;
        return;
    }
    while (curr->next != nullptr && (curr->row * this->precedence_factor + curr->col < new_node->row * this->precedence_factor + new_node->col))
    {
        curr = curr->next;
    }
    if (curr->row * this->precedence_factor + curr->col == new_node->row * this->precedence_factor + new_node->col)
    {
        if (curr->previous != nullptr)
        {
            curr->previous->next = new_node;
            new_node->previous = curr->previous;
        }
        if (curr->next != nullptr)
        {
            curr->next->previous = new_node;
            new_node->next = curr->next;
        }
        if (new_node->next == nullptr)
        {
        }
    }
    else if (curr->row * this->precedence_factor + curr->col > new_node->row * this->precedence_factor + new_node->col)
    {
        if (curr->previous != nullptr)
        {
            curr->previous->next = new_node;
            new_node->previous = curr->previous;
        }
        else
        {
            this->head = new_node;
        }
        new_node->next = curr;
        curr->previous = new_node;
        this->list_size++;
    }
    else
    {
        new_node->previous = curr;
        curr->next = new_node;
        this->list_size++;
    }
    return;
}
void checkError(int size)
{
    if (size == 0)
    {
        throw std::runtime_error("Empty Matrix");
    }
}
int Matrix::getSize() const
{
    try
    {
        checkError(this->list_size);
    }
    catch (const std::exception& e)
    {
        return 0;
    }
    return this->list_size;
}
int Matrix::getMaxRow()
{
    try
    {
        checkError(this->list_size);
    }
    catch (const std::exception& e)
    {
        return 0;
    }
    return this->max_row_index + 1;
}
int Matrix::getMaxCol()
{
    try
    {
        checkError(this->list_size);
    }
    catch (const std::exception& e)
    {
        return 0;
    }
    return this->max_col_index + 1;
}
void Matrix::printMatrix()
{
    Node* curr = this->head;
    curr = this->head;
    try
    {
        checkError(this->list_size);
    }
    catch (const std::exception& e)
    {
        return;
    }
    for (unsigned int i = 0; i <= this->max_row_index; i++)
    {
        for (unsigned int j = 0; j <= this->max_col_index; j++)
        {
            if (curr != nullptr && curr->row == i && curr->col == j)
            {
                std::cout << curr->data << " ";
                curr = curr->next;
            }
            else
            {
                std::cout << 0 << " ";
            }
        }
        std::cout << std::endl;
    }
}
Matrix Matrix::operator*(const Matrix& other)
{
    Matrix result;
    if (this->max_col_index != other.max_row_index || this->head == nullptr || other.head == nullptr)
    {
        std::cout << "Matrix dimensions do not match or an empty matrix has been passed." << std::endl;
        return result;
    }
    else
    {
        result.setMaxRow(this->max_row_index);
        result.setMaxCol(other.max_col_index);
        Node* curr_one = this->head;
        Node* curr_other = other.head_vertical;
        for (unsigned int i = 0; i <= this->max_row_index; i++)
        {
            for (unsigned int j = 0; j <= other.max_col_index; j++)
            {
                if (curr_one == nullptr || curr_other == nullptr)
                {
                    break;
                }
                Node* curr_one_a = curr_one;
                Node* curr_other_a = curr_other;
                int sum = 0;
                for (unsigned int k = 0; k <= this->max_col_index; k++)
                {
                    if (curr_one_a != nullptr && curr_other_a != nullptr && curr_one_a->row == i && curr_one_a->col == k && curr_other_a->row == k && curr_other_a->col == j)
                    {
                        sum += curr_one_a->data * curr_other_a->data;
                        curr_one_a = curr_one_a->next;
                        curr_other_a = curr_other_a->below;
                    }
                    if (curr_one_a != nullptr && curr_other_a != nullptr && curr_one_a->row == i && curr_other_a->col == j)
                    {
                        if (curr_one_a->col <= k)
                        {
                            curr_one_a = curr_one_a->next;
                        }
                        if (curr_other_a->row <= k)
                        {
                            curr_other_a = curr_other_a->below;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                while (curr_other != nullptr && curr_other->col <= j)
                {
                    curr_other = curr_other->below;
                }
                if (sum != 0)
                {
                    result.addElement(sum, i, j);
                }
            }
            while (curr_one != nullptr && curr_one->row <= i)
            {
                curr_one = curr_one->next;
            }
            curr_other = other.head_vertical;
        }
    }
    return result;
}
Matrix Matrix::operator+(const Matrix& other)
{
    Matrix result;
    if (this->max_row_index != other.max_row_index || this->max_col_index != other.max_col_index || this->head == nullptr || other.head == nullptr)
    {
        std::cout << "Matrix dimensions do not match or an empty matrix has been passed." << std::endl;
        return result;
    }
    else
    {
        result.setMaxRow(this->max_row_index);
        result.setMaxCol(this->max_col_index);
        Node* curr_one = head;
        Node* curr_other = other.head;
        for (unsigned int i = 0; i <= max_row_index; i++)
        {
            for (unsigned int j = 0; j <= max_col_index; j++)
            {
                int sum = 0;
                if (curr_one->row == i && curr_one->col == j && curr_other->row == i && curr_other->col == j)
                {
                    sum = curr_one->data + curr_other->data;
                    if (curr_one->next != nullptr)
                    {
                        curr_one = curr_one->next;
                    }
                    if (curr_other->next != nullptr)
                    {
                        curr_other = curr_other->next;
                    }
                }
                else if ((curr_one->row == i && curr_one->col == j) && (curr_other->row != i || curr_other->col != j))
                {
                    sum = curr_one->data;
                    if (curr_one->next != nullptr)
                    {
                        curr_one = curr_one->next;
                    }
                }
                else if ((curr_one->row != i || curr_one->col != j) && curr_other->row == i && curr_other->col == j)
                {
                    sum = curr_other->data;
                    if (curr_other->next != nullptr)
                    {
                        curr_other = curr_other->next;
                    }
                }
                if (sum > 0)
                {
                    result.addElement(sum, i, j);
                }
            }
        }
        return result;
    }
}
bool Matrix::operator=(const Matrix& other)
{
    if (getSize() != other.getSize())
    {
        return false;
    }
    return true;
}
void Matrix::writeFile(std::string file)
{
    Node* temp = this->head;
    try
    {
        checkError(this->list_size);
    }
    catch (const std::exception& e)
    {
        return;
    }
    std::ofstream output_file(file);
    for (unsigned int i = 0; i <= this->max_row_index; i++)
    {
        for (unsigned int j = 0; j <= this->max_col_index; j++)
        {
            if (temp != nullptr && temp->row == i && temp->col == j)
            {
                output_file << temp->data << " ";
                temp = temp->next;
            }
            else
            {
                output_file << "0 ";
            }
        }
        output_file << std::endl;
    }
}
void Matrix::readFile(std::string file_name)
{
    this->list_size = 0;
    this->max_col_index = 0;
    this->max_row_index = 0;
    this->precedence_factor = 0;
    this->head = nullptr;
    this->head_vertical = nullptr;
    std::ifstream file(file_name);
    if (!file)
    {
        return;
    }
    std::string str;
    int i = 0;
    int j = 0;
    while (std::getline(file, str))
    {
        std::istringstream ss(str);
        int token;
        j = 0;
        while (ss >> token)
        {
            if (token != 0)
            {
                addElement(token, i, j);
            }
            j++;
        }
        i++;
    }
    setMaxRow(i - 1);
    setMaxCol(j - 1);
    Node* temp1 = this->head;
    this->head_vertical = this->head;
    while (temp1 != nullptr)
    {
        Node* temp2 = this->head;
        while (temp2 != nullptr)
        {
            if (temp2->row + temp2->col * this->precedence_factor > temp1->row + temp1->col * this->precedence_factor && (temp1->below == nullptr || temp2->row + temp2->col * this->precedence_factor < temp1->below->row + temp1->below->col * this->precedence_factor))
            {
                temp1->below = temp2;
            }
            if (temp2->row + temp2->col * this->precedence_factor < this->head_vertical->row + this->head_vertical->col * this->precedence_factor)
            {
                this->head_vertical = temp2;
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
}
void Matrix::randomMatrix(int rows, int columns, int lower_bound, int upper_bound, int nonzero)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> x_distr(0, columns - 1);
    std::uniform_int_distribution<int> y_distr(0, rows - 1);
    std::uniform_int_distribution<int> data_distr(lower_bound, upper_bound);
    while (getSize() != nonzero)
    {
        int candidate_data = 0;
        while (candidate_data == 0)
        {
            candidate_data = data_distr(generator);
        }
        addElement(candidate_data, y_distr(generator), x_distr(generator));
    }
    setMaxCol(columns - 1);
    setMaxRow(rows - 1);
    Node* temp1 = this->head;
    this->head_vertical = this->head;
    while (temp1 != nullptr)
    {
        Node* temp2 = this->head;
        while (temp2 != nullptr)
        {
            if (temp2->row + temp2->col * this->precedence_factor > temp1->row + temp1->col * this->precedence_factor && (temp1->below == nullptr || temp2->row + temp2->col * this->precedence_factor < temp1->below->row + temp1->below->col * this->precedence_factor))
            {
                temp1->below = temp2;
            }
            if (temp2->row + temp2->col * this->precedence_factor < this->head_vertical->row + this->head_vertical->col * this->precedence_factor)
            {
                this->head_vertical = temp2;
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
}
Matrix::~Matrix()
{
    deleteMatrix(this->head);
}
void Matrix::deleteMatrix(Node* node)
{
    while (node)
    {
        Node* next = node->next;
        delete node;
        node = next;
    }
}
