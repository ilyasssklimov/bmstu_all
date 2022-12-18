import "./SearchButton.css"
import searchButton from "../../resources/searchButtonDisabled.svg"


const SearchButton = () => {
    return (
        <input type="image" src={searchButton} alt="Поиск" className="search_button" disabled/>
    )
}

export default SearchButton;