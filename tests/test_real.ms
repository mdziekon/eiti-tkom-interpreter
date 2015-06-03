function isDiag(matrix)
{
    if (!(matrix))
    {
        return 0;
    }
    var mSize = size(matrix);
    print(mSize);
    if (mSize[0][0] != mSize[0][1])
    {
        return 0;
    }

    var i = 0;
    while (i < mSize[0][0])
    {
        var j = 0;
        while (j < mSize[0][1])
        {
            if (i != j && matrix[i][j] != 0)
            {
                return 0;
            }

            j = j + 1;
        }

        i = i + 1;
    }

    return 1;
}



function main()
{
    var gen = generate(3, 3, 0);

    gen[1] = [ 0, 2, 0];
    print(gen);
    print(isDiag(gen));

    printEmpty();

    gen = resize(gen, 4, 4, 1);
    print(gen);
    print(isDiag(resize(gen, 4, 4, 1)));

    return 0;
}
