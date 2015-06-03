

function myPrint(x)
{
    print(transpose([ 1, 2, 3; 4, 5, 6; 7, 8, 9; 10, InfiNity, 12]));
    printEmpty();
    print(generate([2], 3, [2]));
    printEmpty();
    print(resize(generate([2], 3, [2]), 3, 4, -Infinity));
    printEmpty();
    print(size(generate(2, 11, 2)));

    return 1;
}

function main()
{
    var abc = [1,2];
    myPrint(abc);

    return 1;
}
