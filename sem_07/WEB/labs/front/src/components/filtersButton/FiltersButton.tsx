import "./FiltersButton.css"
import filtersButtonDisabled from "../../resources/filtersButtonDisabled.svg"


const FiltersButton = () => {
    return (
        <input type="image" src={filtersButtonDisabled} alt="Фильтры" className="filters_button" disabled/>
    )
}

export default FiltersButton;