/**
  Handle the wheel usage, scroll or zoom depending on pressed modifiers
  */
function handleWheel(wheel)
{
    // Normalize to factors between 0.8 and 1.2
    let factor = (((wheel.angleDelta.y / 120)+1) / 5 ) + 0.8;
    
    if (wheel.modifiers & Qt.ControlModifier)
    {
        zoom(factor);
    }
    // angleDelta.x is the "horizontal scroll" mode some mouses support by
    // e.g. pushing the scroll button to the left/right. Make sure not to
    // scroll vertically when a "horizontal scroll" is performed
    else if(wheel.angleDelta.x === 0)
    {
        if(factor > 1)
            flick(listView.scrollSpeed);
        else
            flick(-listView.scrollSpeed);
    }
}

function updateCurrentPageCounter()
{
    // Calculate the current page based on contentY and the zoom
    let pageHeight = listView.currentItem.height;
    let currentPos = listView.contentY - listView.originY + root.height/2;
    let pageNumber = Math.floor(currentPos / pageHeight);
    
    if(pageNumber !== root.document.currentPage)
    {
        root.document.currentPage = pageNumber;
    }
}

/**
  Changes the current move direction of the listview, without actually
  moving visibly. This is neccessary since the listview only chaches
  delegates in the direction of the current move direction.
  If we e.g. scroll downwards and then go to the previousPage
  by setting the contentY, the previous pages are not cached
  which might lead to visible loading while moving through the
  book with the arrow keys
  */
function setMoveDirection(direction)
{
    if(direction === "up")
    {
        listView.flick(0, -1000);
        listView.cancelFlick();
    }
    else if(direction === "down")
    {
        listView.flick(0, 1000);
        listView.cancelFlick();
    }
}

function zoom(factor)
{
    let newWidth = listView.contentWidth * factor;
    if (newWidth < listView.normalWidth / 6 || newWidth > listView.normalWidth * 5)
        return;
    
    listView.resizeContent(Math.round(newWidth),
                           Math.round(newWidth / listView.currentItem.pageRatio),
                           Qt.point(0, 0));
    listView.returnToBounds();
}

function flick(factor)
{
    listView.flick(0, factor);
}

function nextPage()
{
    let currentPageStartY = root.document.currentPage * listView.currentItem.height;
    let nextPageY = currentPageStartY + listView.currentItem.height;
    let diff = nextPageY - listView.contentY;
    listView.contentY = nextPageY + listView.originY;
    
    setMoveDirection("up");
}

function previousPage()
{
    let currentPageStartY = root.document.currentPage * listView.currentItem.height;
    let nextPageY = currentPageStartY - listView.currentItem.height;
    listView.contentY = nextPageY + listView.originY;
    
    setMoveDirection("down");
}