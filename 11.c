#include <stdio.h>
int main()
{
    int choice;
    while (1)
    {
        printf("\n1. Paging");
        printf("\n2. Segmentation");
        printf("\n3. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            int page_size, logical, page_no, offset;
            printf("Enter page size: ");
            scanf("%d", &page_size);
            printf("Enter logical address: ");
            scanf("%d", &logical);
            page_no = logical / page_size;
            offset = logical % page_size;
            printf("Page Number = %d\n", page_no);
            printf("Offset = %d\n", offset);
        }
        else if (choice == 2)
        {
            int segment, offset;
            printf("Enter segment number: ");
            scanf("%d", &segment);
            printf("Enter offset: ");
            scanf("%d", &offset);
            printf("Logical Address = <%d , %d>\n", segment, offset);
        }
        else if (choice == 3)
        {
            break;
        }
        else
        {
            printf("Invalid choice\n");
        }
    }
    return 0;
}