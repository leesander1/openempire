#include "Points.h"

#include "Util.h"

#include <assert.h>

Points Points_New(const int32_t max)
{
    Point* point = UTIL_ALLOC(Point, max);
    UTIL_CHECK(point);
    const Points points = { point, 0, max };
    return points;
}

void Points_Free(const Points points)
{
    free(points.point);
}

Points Points_Append(Points points, const Point point)
{
    assert(points.count < points.max);
    points.point[points.count++] = point;
    return points;
}

Points Points_Cat(Points a, const Points b)
{
    const int32_t new_size = a.count + b.count;
    if(new_size > 0)
    {
        Point* const temp = UTIL_REALLOC(a.point, Point, new_size);
        UTIL_CHECK(temp);
        a.point = temp;
        a.max = new_size;
        for(int32_t i  = 0; i < b.count; i++)
            a = Points_Append(a, b.point[i]);
    }
    return a;
}

void Points_Print(const Points points)
{
    for(int32_t i = 0; i < points.count; i++)
        printf("%d %d\n", points.point[i].x, points.point[i].y);
    putchar('\n');
}
