// ┌┐ ┬─┐┌─┐┬ ┬┌─┐┌┬┐┬  ┌─┐ | Bootable Rescue System Tools
// ├┴┐├┬┘└─┐└┬┘└─┐ │ │  └─┐ | @author Luís Ferreira
// └─┘┴└─└─┘ ┴ └─┘ ┴ ┴─┘└─┘ | @license GNU Public License v3

void * get_physaddr(void * virtualaddr)
{
    unsigned long pdindex = (unsigned long)virtualaddr >> 22;
    unsigned long ptindex = (unsigned long)virtualaddr >> 12 & 0x03FF;
    unsigned long * pd = (unsigned long *)0xFFFFF000;
    unsigned long * pt = ((unsigned long *)0xFFC00000) + (0x400 * pdindex);
    return (void *)((pt[ptindex] & ~0xFFF) + ((unsigned long)virtualaddr & 0xFFF));
}

void map_page(void * physaddr, void * virtualaddr, unsigned int flags)
{
    unsigned long pdindex = (unsigned long)virtualaddr >> 22;
    unsigned long ptindex = (unsigned long)virtualaddr >> 12 & 0x03FF;
    unsigned long * pd = (unsigned long *)0xFFFFF000;
    unsigned long * pt = ((unsigned long *)0xFFC00000) + (0x400 * pdindex);
    pt[ptindex] = ((unsigned long)physaddr) | (flags & 0xFFF) | 0x01;
}